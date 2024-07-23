/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananari      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 07:56:27 by aelison           #+#    #+#             */
/*   Updated: 2024/07/23 16:37:00 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clear_mutex_leak(t_rules *rule)
{
	int	i;

	i = 0;
	while (i < rule->nb_philo)
	{
		pthread_mutex_destroy(&rule->fork_array[i].m);
		i++;
	}
	pthread_mutex_destroy(&rule->end);
	pthread_mutex_destroy(&rule->data);
	pthread_mutex_destroy(&rule->message);
	free(rule->philo_array);
	free(rule->fork_array);
}

int	main(int argc, char **argv)
{
	t_rules	rule;

	if (ft_errors(argc, argv) == 1)
		return (EXIT_FAILURE);
	ft_init_rule(&rule, argv, argc);
	ft_create_pthread(&rule, rule.nb_philo);
	ft_clear_mutex_leak(&rule);
	return (EXIT_SUCCESS);
}
