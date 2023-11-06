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
# define TAKE "take"
# define DROP "drop"
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

typedef struct s_philo
{
	struct s_data	*data;
	int				id_nbr;
	int				eat_cont;
	int				status;
	int				finish;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}				t_philo;

typedef struct s_data
{
	pthread_t		*tideath;
	pthread_t		*tid;
	t_philo			*philo;
	int				meals_nbr;
	int				id_philo;
	int				max_philo;
	int				one_dead;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	msg;
}				t_data;

int			ft_atoi(const char *str);
uint64_t	get_time(void);
int			set_malloc(t_data *data);
int			ft_strcmp(const char *s1, const char *s2);
int			set_data(t_data *data, int argc, char **argv);
int			check_data(t_data *data, int argc);
int			set_philo(t_data *data);
int			set_fork(t_data *data);
int			set(t_data *data, int argc, char **argv);
void		alone(t_philo *philo);
void		reset_timer_death(t_philo *philo);
void		drop_and_take(t_philo *philo, char *info);
void		ft_sleep(uint64_t timetosleep, t_philo *philo);
void		ft_free(t_data *data);
void		message(t_philo *philo, char *message);
#endif