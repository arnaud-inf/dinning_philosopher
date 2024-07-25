/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananari      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 07:54:49 by aelison           #+#    #+#             */
/*   Updated: 2024/07/25 09:45:31 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_disp(t_philo *ph, char *m)
{
	long	t_stamp;

	pthread_mutex_lock(ph->message);
	pthread_mutex_lock(ph->end);
	if (ph->state != is_dead && *ph->end_routine != 1)
	{
		t_stamp = ft_elapsed_time(*ph->start_routine);
		printf("%-10ld %d %s\n", t_stamp, ph->id, m);
	}
	pthread_mutex_unlock(ph->end);
	pthread_mutex_unlock(ph->message);
}

int	ft_sleeping(t_philo *ph)
{
	pthread_mutex_lock(ph->data);
	if (ph->state == is_dead || *ph->end_routine == 1)
	{
		pthread_mutex_unlock(ph->data);
		return (1);
	}
	ph->state = thinking;
	pthread_mutex_unlock(ph->data);
	ft_disp(ph, "is sleeping");
	ft_usleep(ph->t_sleep, ph);
	return (0);
}

int	ft_thinking(t_philo *ph)
{
	pthread_mutex_lock(ph->data);
	if (ph->state == is_dead || *ph->end_routine == 1)
	{
		pthread_mutex_unlock(ph->data);
		return (1);
	}
	ph->state = thinking;
	pthread_mutex_unlock(ph->data);
	ft_disp(ph, "is thinking");
	return (0);
}

void	ft_eating_aux(t_philo *ph)
{
	ft_disp(ph, "has taken a fork");
	ft_disp(ph, "is eating");
	pthread_mutex_lock(ph->data);
	ph->lst_meal = ft_get_time();
	ph->nb_meals++;
	ph->state = eating;
	if (ph->nb_meals == ph->nb_have_to_eat)
		*ph->is_full = *ph->is_full + 1;
	pthread_mutex_unlock(ph->data);
	ft_usleep(ph->t_eat, ph);
}

int	ft_eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->first_f->m);
	ft_disp(ph, "has taken a fork");
	pthread_mutex_lock(ph->data);
	if (ph->second_f == NULL)
	{
		ph->lst_meal = ft_get_time();
		ft_usleep(ph->t_die, ph);
		pthread_mutex_unlock(&ph->first_f->m);
		pthread_mutex_unlock(ph->data);
		return (1);
	}
	pthread_mutex_unlock(ph->data);
	pthread_mutex_lock(&ph->second_f->m);
	ft_eating_aux(ph);
	pthread_mutex_unlock(&ph->second_f->m);
	pthread_mutex_unlock(&ph->first_f->m);
	return (0);
}
