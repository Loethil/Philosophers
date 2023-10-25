/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:24:12 by mbatteux          #+#    #+#             */
/*   Updated: 2023/10/12 13:37:30 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	drop_and_take(t_philo *philo, char *info)
{
	if (ft_strcmp(info, TAKE) == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		message(philo, "has taken l fork");
		pthread_mutex_lock(philo->r_fork);
		message(philo, "has taken r fork");
	}
	else if (ft_strcmp(info, DROP) == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		message(philo, "drop l fork");
		pthread_mutex_unlock(philo->r_fork);
		message(philo, "drop r fork");
	}
}

void	eat(t_philo *philo)
{
	drop_and_take(philo, TAKE);
	pthread_mutex_lock(&philo->lock);
	message(philo, "is eating");
	usleep(philo->data->eat_time * 1000);
	philo->eat_cont++;
	pthread_mutex_unlock(&philo->lock);
	drop_and_take(philo, DROP);
}

void	*routine(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)data_pointer;
	message(philo, "is created");
	while (philo->eat_cont < philo->data->meals_nbr)
	{
		eat(philo);
		message(philo, "is sleeping");
		usleep(philo->data->sleep_time * 1000);
		message(philo, "is thinking");
	}
	return (NULL);
}

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->max_philo)
	{
		pthread_create(&data->tid[i], NULL, &routine, &data->philo[i]);
		usleep(2000);
		i++;
	}
	i = 0;
	while (i < data->max_philo)
	{
		pthread_join(data->tid[i], NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (0);
	set(&data, argc, argv);
	create_thread(&data);
	return (0);
}
