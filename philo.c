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

int	main(int argc, char **argv)
{
	t_philo	philo1;
	struct	timeval	current_time;
	long long int	time;

	if (argc != 3)
		return (0);
	gettimeofday(&current_time, NULL);
	// printf("micro seconds : %ld\n", current_time.tv_usec);
	time = current_time.tv_usec / 1000;
	philo1.status = 0;
	while (philo1.status == 0)
	{
		gettimeofday(&current_time, NULL);
		philo1.horloge = current_time.tv_usec / 1000;
		if(philo1.horloge >= time + 10)
			philo1.status = 1;
		else if (philo1.status == 0)
			printf("philo1 alive and waiting to die at time = %lld ms\n", philo1.horloge);
	}
	printf("philo1 is dead at time = %lld ms \n", philo1.horloge);
	return (0);
}
