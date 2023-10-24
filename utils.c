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

uint64_t	get_time(void)
{
	struct timeval	clock;
	uint64_t		time;

	gettimeofday(&clock, NULL);
	time = (clock.tv_sec * 1000) + (clock.tv_usec / 1000);
	return (time);
}

void	message(t_philo *philo, char *message)
{
	uint64_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->msg);
	printf("[%ldms] %d %s\n", time, philo->id_nbr, message);
	pthread_mutex_unlock(&philo->data->msg);
}
