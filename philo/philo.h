/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananari      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 07:55:30 by aelison           #+#    #+#             */
/*   Updated: 2024/07/25 09:43:55 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_state
{
	thinking,
	eating,
	sleeping,
	is_dead
}	t_state;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	m;
}	t_fork;

typedef struct s_philo
{
	int				id;
	long			nb_meals;
	size_t			lst_meal;
	long			nb_have_to_eat;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	t_state			state;
	pthread_t		p;
	int				*is_full;
	int				*end_routine;
	size_t			*start_routine;
	t_fork			*first_f;
	t_fork			*second_f;
	pthread_mutex_t	*message;
	pthread_mutex_t	*data;
	pthread_mutex_t	*end;
}	t_philo;

typedef struct s_rules
{
	int				is_full;
	int				nb_philo;
	int				end_routine;
	long			nb_have_to_eat;
	size_t			start_routine;
	t_philo			*philo_array;
	t_fork			*fork_array;
	pthread_t		monitor;
	pthread_mutex_t	end;
	pthread_mutex_t	data;
	pthread_mutex_t	message;
}	t_rules;

int		ft_strlen(char *str);
int		ft_errors(int argc, char **argv);
int		ft_putstr_fd(char *str, int fd);
int		ft_init_mutex(pthread_mutex_t m);
int		ft_destroy_mutex(pthread_mutex_t m);
int		ft_create_pthread(t_rules *r, int nb_ph);
int		ft_eating(t_philo *ph);
int		ft_thinking(t_philo *ph);
int		ft_sleeping(t_philo *ph);
int		ft_usleep(size_t ms, t_philo *ph);
int		ft_clear_all_mutex(t_rules *rule);
void	*ft_monitor(void *arg);
void	ft_init_rule(t_rules *rule, char **argv, int argc);
void	ft_disp(t_philo *ph, char *m);
size_t	ft_get_time(void);
size_t	ft_elapsed_time(long start_time);
size_t	ft_atoi(char *str);
#endif
