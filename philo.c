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


void	*eat(t_data *stru)
{
	uint64_t	time;

	time = get_time() - stru->base_time;
	printf("[%ldms] i %d start eating\n", time, stru->sign_philo);
	if (stru->sign_philo == 1)
	{
		pthread_mutex_lock(&stru->forks[stru->sign_philo]);
		pthread_mutex_lock(&stru->forks[stru->num_philo]);
		printf("[%ldms] i have r = %d, and l = %d\n", time, stru->num_philo, stru->sign_philo);
		ft_usleep(stru->eat_time);
		time = get_time() - stru->base_time;
		pthread_mutex_unlock(&stru->forks[stru->sign_philo]);
		pthread_mutex_unlock(&stru->forks[stru->num_philo]);
		printf("[%ldms] i %d have finished eating\n\n", time, stru->sign_philo);
	}
	else
	{
		pthread_mutex_lock(&stru->forks[stru->sign_philo]);
		pthread_mutex_lock(&stru->forks[stru->sign_philo - 1]);
		printf("[%ldms] i have r = %d, and l = %d\n", time, stru->sign_philo - 1, stru->sign_philo);
		ft_usleep(stru->eat_time);
		time = get_time() - stru->base_time;
		pthread_mutex_unlock(&stru->forks[stru->sign_philo]);
		pthread_mutex_unlock(&stru->forks[stru->sign_philo - 1]);
		printf("[%ldms] i %d have finished eating\n\n", time, stru->sign_philo);
	}
	return (NULL);
}

void	*routine(void *data)
{
	t_data	*stru;

	stru = (t_data *)data;
	eat(stru);
	stru->sign_philo++;
	return (NULL);
}

int	start(t_data *data, char **argv)
{
	int	i = 0;

	setting_data(data, argv);
	pthread_mutex_init(&data->lock, NULL);
	data->tid = malloc(data->num_philo * sizeof(t_data));
	while (i < data->num_philo)
	{
		pthread_create(&data->tid[i], NULL, &routine, data);
		pthread_join(data->tid[i], NULL);
		i++;
	}
	return (0);
}


int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc != 5)
		return (0);
	start(&data, argv);
	return (0);
}