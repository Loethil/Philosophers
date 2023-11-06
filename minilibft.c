/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:14:55 by mbatteux          #+#    #+#             */
/*   Updated: 2023/10/24 16:14:56 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_atoi(const char *str)
{
	int			o;
	long int	res;

	o = 0;
	res = 0;
	while (str[o])
	{
		if (str[o] >= 48 && str[o] <= 57)
			res = res * 10 + str[o++] - '0';
		else
			return (0);
	}
	if (res < 0 || res > 2147483647)
		return (0);
	return (res);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	if (s2[i])
		return (-1);
	return (0);
}

void	alone(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	message(philo, "has taken a fork");
	while (philo->status == 0)
		usleep(5);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->msg);
	while (i < data->max_philo)
	{
		pthread_mutex_destroy(&data->philo[i].lock);
		pthread_mutex_destroy(&data->forks[i++]);
	}
	if (data->one_dead == 0)
		message(data->philo, "end of simulation");
	free(data->philo);
	free(data->forks);
	free(data->tid);
	free(data->tideath);
}

int	check_data(t_data *data, int argc)
{
	if (argc == 6 && data->meals_nbr <= 0)
		return (1);
	if (data->max_philo <= 0)
		return (1);
	if (data->death_time <= 0)
		return (1);
	if (data->eat_time <= 0)
		return (1);
	if (data->sleep_time <= 0)
		return (1);
	if (data->start_time <= 0)
		return (1);
	return (0);
}
