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

uint64_t	get_time()
{
	struct	timeval	clock;
	uint64_t	time;

	gettimeofday(&clock, NULL);
	time = (clock.tv_sec * 1000) + (clock.tv_usec / 1000);
	return (time);
}

int	setting_data(t_data *data, char **argv)
{
	data->sign_philo = 1;
	data->base_time = get_time();
	data->num_philo = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->forks = malloc(data->num_philo * sizeof(pthread_mutex_t));
	return (0);
}

int	ft_usleep(uint64_t time)
{
	usleep(time * 1000);
	return (0);
}