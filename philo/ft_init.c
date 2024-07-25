/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananari      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 07:55:04 by aelison           #+#    #+#             */
/*   Updated: 2024/07/24 08:02:10 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_create_ph_aux(int id, int nb_ph, t_fork *f, t_philo *res)
{
	if (res->id == nb_ph)
	{
		res->first_f = f + id;
		res->second_f = f;
	}
	else if (res->id % 2 == 0)
	{
		res->first_f = f + id;
		res->second_f = f + id + 1;
	}
	else
	{
		res->first_f = f + id + 1;
		res->second_f = f + id;
	}
}

static t_philo	ft_create_ph(int id, int nb_ph, t_fork *f)
{
	t_philo	res;

	res.id = id + 1;
	res.nb_meals = 0;
	res.lst_meal = 0;
	res.state = -1;
	if (nb_ph == 1)
	{
		res.first_f = f;
		res.second_f = NULL;
	}
	else
		ft_create_ph_aux(id, nb_ph, f, &res);
	return (res);
}

static t_fork	*ft_create_fork(int nb_ph)
{
	int		i;
	t_fork	*res;

	i = 0;
	res = malloc(sizeof(t_fork) * nb_ph);
	if (!res)
		return (NULL);
	while (i < nb_ph)
	{
		res[i].id = i + 1;
		if (pthread_mutex_init(&res[i].m, NULL) != 0)
		{
			free(res);
			return (NULL);
		}
		i++;
	}
	return (res);
}

static t_philo	*ft_create_all_ph(t_rules *rules, long t_die,
					long t_eat, long t_sleep)
{
	t_philo	*res;
	int		i;

	res = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!res)
		return (NULL);
	i = 0;
	while (i < rules->nb_philo)
	{
		res[i] = ft_create_ph(i, rules->nb_philo, rules->fork_array);
		res[i].nb_have_to_eat = rules->nb_have_to_eat;
		res[i].t_die = t_die;
		res[i].t_eat = t_eat;
		res[i].t_sleep = t_sleep;
		res[i].end = &rules->end;
		res[i].data = &rules->data;
		res[i].message = &rules->message;
		res[i].is_full = &rules->is_full;
		res[i].start_routine = &rules->start_routine;
		res[i].end_routine = &rules->end_routine;
		i++;
	}
	return (res);
}

void	ft_init_rule(t_rules *rule, char **argv, int argc)
{
	rule->nb_philo = ft_atoi(argv[1]);
	rule->is_full = 0;
	rule->end_routine = 0;
	rule->start_routine = 0;
	pthread_mutex_init(&rule->end, NULL);
	pthread_mutex_init(&rule->data, NULL);
	pthread_mutex_init(&rule->message, NULL);
	if (argc == 6)
		rule->nb_have_to_eat = ft_atoi(argv[5]);
	else
		rule->nb_have_to_eat = -1;
	rule->fork_array = ft_create_fork(rule->nb_philo);
	if (rule->fork_array == NULL)
		ft_clear_all_mutex(rule);
	rule->philo_array = ft_create_all_ph(rule, ft_atoi(argv[2]),
			ft_atoi(argv[3]), ft_atoi(argv[4]));
}
