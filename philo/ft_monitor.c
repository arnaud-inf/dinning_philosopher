/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananari      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 07:56:04 by aelison           #+#    #+#             */
/*   Updated: 2024/07/24 08:08:02 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_chek_full(t_philo *ph, int nb_ph)
{
	pthread_mutex_lock(ph->data);
	if (*ph->is_full == nb_ph)
	{
		pthread_mutex_lock(ph->end);
		*ph->end_routine = 1;
		pthread_mutex_unlock(ph->end);
		pthread_mutex_unlock(ph->data);
		return (1);
	}
	pthread_mutex_unlock(ph->data);
	return (0);
}

int	ft_is_nb_meal_full(t_philo *ph, int nb_philo)
{
	int	i;

	i = 0;
	if (ph[0].nb_have_to_eat == -1)
		return (0);
	while (i < nb_philo)
	{
		if (ft_chek_full(&ph[i], nb_philo) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_death(t_philo *ph)
{
	pthread_mutex_lock(ph->data);
	if (ph->lst_meal == 0)
	{
		pthread_mutex_unlock(ph->data);
		return (0);
	}
	if (ft_elapsed_time(ph->lst_meal) > ph->t_die)
	{
		ft_disp(ph, "died");
		pthread_mutex_lock(ph->end);
		ph->state = is_dead;
		*ph->end_routine = 1;
		pthread_mutex_unlock(ph->end);
		pthread_mutex_unlock(ph->data);
		return (1);
	}
	pthread_mutex_unlock(ph->data);
	return (0);
}

int	ft_is_dead(t_philo *ph, int nb_philo)
{
	int		i;

	i = 0;
	while (i < nb_philo)
	{
		if (ft_check_death(&ph[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_rules	*rule;
	t_philo	*ph;
	int		nb;

	rule = (t_rules *)arg;
	ph = rule->philo_array;
	nb = rule->nb_philo;
	while (1)
	{
		if ((ft_is_dead(ph, nb) == 1) || (ft_is_nb_meal_full(ph, nb) == 1))
			break ;
		usleep(0);
	}
	return (NULL);
}
