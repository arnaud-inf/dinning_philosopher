/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananari      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 07:56:17 by aelison           #+#    #+#             */
/*   Updated: 2024/07/22 07:56:19 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	res;

	res = 0;
	while (str[res] != '\0')
		res++;
	return (res);
}

int	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	if (fd == 2)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

size_t	ft_get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

size_t	ft_elapsed_time(long start_time)
{
	return (ft_get_time() - start_time);
}

size_t	ft_atoi(char *str)
{
	size_t	result;
	long	i;

	i = 0;
	result = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}
