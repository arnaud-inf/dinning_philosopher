/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananari      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 07:56:27 by aelison           #+#    #+#             */
/*   Updated: 2024/07/23 16:56:50 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_clear_mutex(pthread_mutex_t t)
{
	if (pthread_mutex_destroy(&t) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_clear_all_mutex(t_rules *rule)
{
	int	i;

	i = 0;
	while (i < rule->nb_philo)
	{
		if (ft_clear_mutex(rule->fork_array[i].m) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	if (ft_clear_mutex(rule->end) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_clear_mutex(rule->data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_clear_mutex(rule->message) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_clear_malloc(t_rules *rule)
{
	free(rule->fork_array);
	free(rule->philo_array);
}

int	main(int argc, char **argv)
{
	t_rules	rule;

	if (ft_errors(argc, argv) == 1)
		return (EXIT_FAILURE);
	ft_init_rule(&rule, argv, argc);
	ft_create_pthread(&rule, rule.nb_philo);
	ft_clear_all_mutex(&rule);
	ft_clear_malloc(&rule);
	return (EXIT_SUCCESS);
}
