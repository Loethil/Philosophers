/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:16:20 by mbatteux          #+#    #+#             */
/*   Updated: 2023/10/24 16:16:21 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	set_malloc(t_data *data)
{
	data->forks = malloc(data->max_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (1);
	data->philo = malloc(data->max_philo * sizeof(t_philo));
	if (!data->philo)
		return (1);
	data->tid = malloc (data->max_philo * sizeof(pthread_t));
	if (!data->tid)
		return (1);
	return (0);
}

void	set_data(t_data *data, int argc, char **argv)
{
	data->meals_nbr = -1;
	if (argc == 6)
		data->meals_nbr = ft_atoi(argv[5]);
	data->max_philo = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->start_time = get_time();
	pthread_mutex_init(&data->msg, NULL);
	if (data->max_philo == 0|| data->death_time == 0 || data->eat_time == 0 \
		|| data->sleep_time == 0 || data->start_time == 0)
		return ;
}

void	set_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->max_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id_nbr = i + 1;
		data->philo[i].eat_cont = 0;
		data->philo[i].status = 0;
		data->philo[i].eating = 0;
		data->philo[i].time_to_die = data->death_time;
		pthread_mutex_init(&data->philo[i].lock, NULL);
		i++;
	}
}

void	set_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->max_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	data->philo[0].l_fork = &data->forks[0];
	data->philo[0].r_fork = &data->forks[data->max_philo - 1];
	i = 1;
	while (i < data->max_philo)
	{
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[i - 1];
		i++;
	}
}

void	set(t_data *data, int argc, char **argv)
{
	set_data(data, argc, argv);
	set_malloc(data);
	set_philo(data);
	set_fork(data);
}
