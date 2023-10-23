/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:08:05 by mbatteux          #+#    #+#             */
/*   Updated: 2023/10/13 15:08:07 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 0 && c <= 9)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	o;
	int	res;

	o = 0;
	res = 0;
	while (str[o] && (ft_isdigit(str[o] - '0') == 1))
		res = res * 10 + str[o++] - '0';
	return (res);
}

uint64_t	get_time(void)
{
	struct	timeval	clock;
	uint64_t	time;

	gettimeofday(&clock, NULL);
	time = (clock.tv_sec * 1000) + (clock.tv_usec / 1000);
	return (time);
}

void	setting_data(t_data *data, char **argv)
{
	int	i = 0;

	if (argv[5])
		data->meals_num = ft_atoi(argv[5]);
	else
		data->meals_num = -1;
	data->sign_philo = 0;
	data->num_philo = ft_atoi(argv[1]);
	data->start_time = get_time();
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->tid = malloc(data->num_philo * sizeof(t_data));
	data->philo = malloc(data->num_philo * (sizeof(t_philo)));
	data->forks = malloc(data->num_philo * sizeof(pthread_mutex_t));
	while (i < data->num_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->msg, NULL);
}

void	setting_philo(t_data *data, t_philo *philo)
{
	philo->data = data;
	philo->number = data->sign_philo;
	philo->eat_cont = 0;
	philo->eating = 0;
	philo->time_to_die = data->start_time + data->death_time;
	philo->l_fork = data->forks[data->sign_philo];
	if (philo->number == 1)
		philo->r_fork = data->forks[data->num_philo];
	philo->r_fork = data->forks[data->sign_philo -1];
}
