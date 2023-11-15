/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:33:19 by maburnet          #+#    #+#             */
/*   Updated: 2023/11/13 18:09:06 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				eat_count;
	long long		time_last_meal;
	int				right_fork;
	int				left_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	long int		philo_nbr;
	long int		t_t_die;
	long int		t_t_eat;
	long int		t_t_sleep;
	long int		nb_of_time_eat;
	int				is_dead;
	int				all_ate;
	long long		starting_time;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	write;
	t_philo			philo[250];
}	t_data;

/* PUT FUNCTIONS */

void		ft_putchar(char c);

void		ft_putstr(char *str);

void		ft_putstr_fd(char *str, int fd);

void		ft_putnbr(int nb);

/* THREADS */

int			ft_start(t_data *data);

void		*thread_routine(void *data);

void		ft_exit(t_data *data, t_philo *philo);

void		ft_check_death(t_data *data, t_philo *philo);

/* PHILO UTILS */

long long	ft_get_time(void);

/* UTILS */

int			ft_isdigit(int c);

long		ft_atol(const char *str);

/* ARGS */

int			ft_verification(char **str, int ac);

#endif
