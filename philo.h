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
	u_int64_t        time_to_die;
}		t_philo;

typedef struct s_data
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	lock;
	pthread_t	*tid;
	t_philo 	*philos;
	int		sign_philo;
	int		num_philo;
	u_int64_t       death_time;
	u_int64_t       eat_time;
	u_int64_t       sleep_time;
	u_int64_t       start_time;
}		t_data;

int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif