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

void	ft_sleep(uint64_t timetosleep, t_philo *philo)
{
	uint64_t	time;

	time = get_time();
	if (philo->data->one_dead == 1)
		return ;
	while ((get_time() - time) < timetosleep)
		usleep(timetosleep / 10);
}

void	message(t_philo *philo, char *message)
{
	uint64_t	time;

	if (philo->data->one_dead == 1)
		return ;
	pthread_mutex_lock(&philo->data->msg);
	time = get_time() - philo->data->start_time;
	printf("[%ldms] %d %s\n", time, philo->id_nbr, message);
	pthread_mutex_unlock(&philo->data->msg);
}

void	reset_timer_death(t_philo *philo)
{
	uint64_t	time;

	if (philo->data->one_dead == 1)
		return ;
	time = get_time() - philo->data->start_time;
	philo->time_to_die = time + philo->data->death_time;
	// printf("philo %d next death time is %ld\n", philo->id_nbr, philo->time_to_die);
}

void	drop_and_take(t_philo *philo, char *info)
{
	if (ft_strcmp(info, TAKE) == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		message(philo, "has taken r fork");
		pthread_mutex_lock(philo->l_fork);
		message(philo, "has taken l fork");
	}
	else if (ft_strcmp(info, DROP) == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		message(philo, "drop r fork");
		pthread_mutex_unlock(philo->l_fork);
		message(philo, "drop l fork");
	}
}
