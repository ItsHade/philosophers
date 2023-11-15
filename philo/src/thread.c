/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:34:35 by maburnet          #+#    #+#             */
/*   Updated: 2023/11/13 18:11:47 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_usleep(long long time, t_data *data)
{
	long long	start;

	start = ft_get_time();
	while (!(data->is_dead))
	{
		if ((ft_get_time() - start) >= time)
			break ;
		usleep(10);
	}
}

void	ft_print_msg(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&(data->write));
	if (!(data->is_dead))
	{
		printf("%lld ", (ft_get_time() - data->starting_time));
		printf("%d ", id + 1);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(&(data->write));
}

void	ft_philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	ft_print_msg(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	ft_print_msg(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->meal_check));
	ft_print_msg(data, philo->id, "is eating");
	philo->time_last_meal = ft_get_time();
	pthread_mutex_unlock(&(data->meal_check));
	ft_usleep(data->t_t_eat, data);
	(philo->eat_count)++;
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
}

void	*thread_routine(void *v_philo)
{
	int		i;
	t_philo	*philo;
	t_data	*data;

	i = 0;
	philo = (t_philo *)v_philo;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(2000);
	while (1)
	{
		// lock 
		// if (data->is_dead)
			// unlock 
			// break ;
		// unlock 
		if (data->all_ate)
			break ;
		ft_philo_eat(philo);
		ft_print_msg(data, philo->id, "is sleeping");
		ft_usleep(data->t_t_sleep, data);
		ft_print_msg(data, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	ft_check_death(t_data *data, t_philo *philo)
{
	int	i;

	while (!(data->all_ate))
	{
		i = -1;
		while (++i < data->philo_nbr && !(data->is_dead))
		{
			pthread_mutex_lock(&(data->meal_check));
			if (ft_get_time() - philo[i].time_last_meal > data->t_t_die)
			{
				ft_print_msg(data, i, "died");
				// lock !!!!
				data->is_dead = 1;
				// unlock !!!!
			}
			pthread_mutex_unlock(&(data->meal_check));
			usleep(100);
		}
		if (data->is_dead == 1)
			break ;
		i = 0;
		while (data->nb_of_time_eat != -1 && i < data->philo_nbr
			&& philo[i].eat_count >= data->nb_of_time_eat)
			i++;
		if (i == data->philo_nbr)
			data->all_ate = 1;
	}
}