/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananari      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 07:55:18 by aelison           #+#    #+#             */
/*   Updated: 2024/07/23 15:32:46 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t ms)
{
	size_t	start;
	size_t	new_ms;

	new_ms = ms / 1000;
	start = ft_get_time();
	while (ft_get_time() - start < new_ms)
	{
		if (usleep(1) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_end_loop(t_philo *ph)
{
	pthread_mutex_lock(ph->end);
	if (*ph->end_routine == 1 || ph->state == is_dead)
	{
		pthread_mutex_unlock(ph->end);
		return (1);
	}
	pthread_mutex_unlock(ph->end);
	return (0);
}

static void	*ft_routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (ft_end_loop(ph) == 0)
	{
		if (ft_eating(ph) == 1)
			break ;
		if (ft_sleeping(ph) == 1)
			break ;
		if (ft_thinking(ph) == 1)
			break ;
	}
	return (NULL);
}

static int	ft_join_thread(t_rules *r, t_philo *ph, int nb_ph)
{
	int	i;

	i = 0;
	r = r;
	if (pthread_join(r->monitor, NULL) != 0)
		return (EXIT_FAILURE);
	while (i < nb_ph)
	{
		if (pthread_join(ph[i].p, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_create_pthread(t_rules *r, int nb_ph)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = r->philo_array;
	nb_ph = nb_ph;
	if (pthread_create(&r->monitor, NULL, &ft_monitor, (void *)r) != 0)
		return (EXIT_FAILURE);
	r->start_routine = ft_get_time();
	while (i < nb_ph)
	{
		if (pthread_create(&ph[i].p, NULL, &ft_routine, (void *)&ph[i]) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	if (ft_join_thread(r, ph, nb_ph) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
