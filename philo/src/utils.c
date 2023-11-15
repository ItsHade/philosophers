/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:34:54 by maburnet          #+#    #+#             */
/*   Updated: 2023/11/13 17:34:57 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	int			i;
	long int	chaine;
	int			sign;

	i = 0;
	chaine = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		chaine = chaine * 10 + str[i] - '0';
		if (chaine > INT_MAX)
			return (-1);
		i++;
	}
	return (sign * chaine);
}

long long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_putstr_fd("gettimeofday() FAILURE\n", 2), -1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
