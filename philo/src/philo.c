/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:34:15 by maburnet          #+#    #+#             */
/*   Updated: 2023/11/13 17:38:34 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_initialize_philo(t_data *data)
{
	int	i;

	i = data->philo_nbr;
	while (--i >= 0)
	{
		data->philo[i].id = i;
		data->philo[i].eat_count = 0;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->philo_nbr;
		data->philo[i].time_last_meal = 0;
		data->philo[i].data = data;
	}
}

int	ft_initialize(t_data *data, char **argv)
{
	int	i;

	data->philo_nbr = ft_atol(argv[1]);
	data->t_t_die = ft_atol(argv[2]);
	data->t_t_eat = ft_atol(argv[3]);
	data->t_t_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->nb_of_time_eat = ft_atol(argv[5]);
	else
		data->nb_of_time_eat = -1;
	i = data->philo_nbr;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (-1);
	}
	if (pthread_mutex_init(&(data->meal_check), NULL))
		return (-1);
	if (pthread_mutex_init(&(data->write), NULL))
		return (-1);
	if (pthread_mutex_init(&(data->dead_check), NULL))
		return (-1);
	ft_initialize_philo(data);
	return (0);
}

int	ft_start(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data->philo;
	data->is_dead = 0;
	data->all_ate = 0;
	data->starting_time = ft_get_time();
	while (i < data->philo_nbr)
	{
		philo[i].time_last_meal = ft_get_time();
		if (pthread_create(
				&(philo[i].thread_id), NULL, thread_routine, &(philo[i])))
			return (-1);
		i++;
	}
	ft_check_death(data, philo);
	ft_exit(data, philo);
	return (0);
}

void	ft_exit(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < data->philo_nbr)
		pthread_detach(philo[i].thread_id);
	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->write));
	pthread_mutex_destroy(&(data->meal_check));
	pthread_mutex_destroy(&(data->dead_check));
}
/*
conditional jump or move depends on uninitialised value
thread_routine (thread.c:77)

 */

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("Error: Arguments invalides\n", 2), -1);
	if (ft_atol(av[1]) > 200)
		return (ft_putstr_fd("Error: Only use 200 philosophers max\n", 2), -1);
	if (ft_verification(av, ac) == -1)
		return (ft_putstr_fd("Error: Not valid numbers\n", 2), -1);
	if (ft_initialize(&data, av) == -1)
		return (ft_putstr_fd("Error: mutex creation\n", 2), -1);
	if (ft_start(&data) == -1)
		return (ft_putstr_fd("Error: thread creation\n", 2), -1);
	return (0);
}
