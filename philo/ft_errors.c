/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananari      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 07:55:41 by aelison           #+#    #+#             */
/*   Updated: 2024/07/23 07:02:48 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i - 1] == '+' && str[i] == '\0')
		return (EXIT_FAILURE);
	if (str[i] != '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_errors(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 6 && argc != 5)
		return (ft_putstr_fd("Error : wrong nb arg (4 or 5 args need)", 2));
	while (argv[i] != NULL)
	{
		if (argv[i][0] == '\0')
			return (ft_putstr_fd("Error : empty arg\n", 2));
		if (ft_check_str(argv[i]) == 1)
			return (ft_putstr_fd("Error : enter positive numbers\n", 2));
		if (ft_strlen(argv[i]) == 1 && argv[i][0] == '0')
			return (ft_putstr_fd("Error : enter value greater than 0\n", 2));
		if (ft_atoi(argv[1]) > 200)
			return (ft_putstr_fd("Error : nb_philo less than 200\n", 2));
		i++;
	}
	return (EXIT_SUCCESS);
}
