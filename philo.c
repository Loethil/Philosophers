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

void	eat(t_data *stru, t_philo *philo)
{
	uint64_t	time;

	time = get_time() - stru->start_time;
	pthread_mutex_lock(&stru->philo->r_fork);
	printf("[%ldms] philo %d taking r fork %d\n", time, philo->number, philo->number -1);
	pthread_mutex_lock(&stru->philo->l_fork);
	printf("[%ldms] philo %d taking l fork %d\n", time, philo->number, philo->number);
	printf("[%ldms] philo %d start eating\n", time, philo->number);
	usleep(stru->eat_time * 1000);
	time = get_time() - stru->start_time;
	pthread_mutex_unlock(&stru->philo->r_fork);
	pthread_mutex_unlock(&stru->philo->l_fork);
	printf("[%ldms] philo %d have finished eating\n", time, philo->number);
	philo->eat_cont++;
}

void	*routine(void *data)
{
	t_data	*stru;
	t_philo	philo;

	setting_philo(data, &philo);
	stru = (t_data *)data;
	printf("[%ldms] philo %d created\n", get_time() - stru->start_time, philo.number);
	eat(stru, &philo);
	return (NULL);
}

int	start(t_data *data)
{
	int	i = 0;

	while (i < data->num_philo)
	{
		data->sign_philo = i + 1;
		pthread_create(&data->tid[i], NULL, &routine, data);
		usleep(1000);
		i++;
	}
	i = 0;
	while(i < data->num_philo)
	{
		pthread_join(data->tid[i], NULL);
		pthread_mutex_destroy(&data->lock);
		i++;
	}
	return (0);
}


int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc < 5 || argc > 6)
		return (0);
	setting_data(&data, argv);
	start(&data);
	return (0);
}