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
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

typedef struct s_philo
{
	struct s_data	*data;
	int		status;
}		t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_t	*tid;
	t_philo 	*philos;
	int		meals_num;
	int		sign_philo;
	int		num_philo;
	uint64_t	base_time;
	uint64_t	death_time;
	uint64_t	eat_time;
	uint64_t	sleep_time;
	uint64_t	start_time;
}		t_data;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
uint64_t	get_time();
int		ft_usleep(uint64_t time);
int		setting_data(t_data *data, char **argv);

#endif