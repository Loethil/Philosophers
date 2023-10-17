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


void	*routine(void *data)
{
	t_data	*stru;

	stru = (t_data *)data;
	pthread_mutex_lock(&stru->lock);
	printf("hello i'm philo number %d\n", stru->sign_philo++);
	if (stru->sign_philo == 0)
	{
		// eat();
		// sleep();
		// think();
		pthread_mutex_lock(&stru->forks[stru->sign_philo]);
		pthread_mutex_lock(&stru->forks[stru->num_philo]);
		printf("i have r = %d, and l = %d\n", stru->sign_philo, stru->num_philo);
	}
	else
	{
		// eat(); x temps tu check la mort dedans
		// sleep();
		// think();
		pthread_mutex_lock(&stru->forks[stru->sign_philo]);
		pthread_mutex_lock(&stru->forks[stru->sign_philo - 1]);
		printf("i have r = %d, and l = %d\n", stru->sign_philo, stru->sign_philo - 1);
	}
	pthread_mutex_unlock(&stru->lock);
	return (NULL);
}

int	start(t_data *data)
{
	int	i = 0;

	data->sign_philo = 0;
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

int	setting_data(t_data *data, char **argv)
{
	struct	timeval	current_time;

	gettimeofday(&current_time, NULL);
	data->num_philo = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->forks = malloc(data->num_philo * sizeof(pthread_mutex_t));
	if (argv[5])
		data->meals_num =  ft_atoi(argv[5]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc != 5)
		return (0);
	setting_data(&data, argv);
	start(&data);
	return (0);
}