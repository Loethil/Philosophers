/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:09:40 by mbatteux          #+#    #+#             */
/*   Updated: 2023/10/12 14:09:42 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_mutex_t	r;
	pthread_mutex_t	l;
	long long        time_to_die;
}		t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_t	*tid;
	t_philo 	*philos;
	int		*tabtest;
	int		meals_num;
	int		sign_philo;
	int		num_philo;
	long long	death_time;
	long long	eat_time;
	long long	sleep_time;
	long long	start_time;
}		t_data;

int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif