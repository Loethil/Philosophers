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

void	message(t_philo *philo, char *message)
{
	uint64_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->msg);
	printf("[%ldms] %d %s\n", time, philo->number, message);
	pthread_mutex_unlock(&philo->data->msg);
}

void	drop_and_take(t_philo *philo, char *info, t_data *data)
{
	if (strcmp(info, TAKE) == 0)
	{
		pthread_mutex_lock(&data->philo->r_fork);
		message(philo, "has taken a fork");
		pthread_mutex_lock(&data->philo->l_fork);
		message(philo, "has taken a fork");
	}
	else if (strcmp(info, DROP) == 0)
	{
		pthread_mutex_unlock(&data->philo->r_fork);
		message(philo, "drop a fork");
		pthread_mutex_unlock(&data->philo->l_fork);
		message(philo, "drop a fork");
	}
	return ;
}

void	eat(t_data *data, t_philo *philo)
{
	message(philo, "is thinking");
	drop_and_take(philo, TAKE, data);
	message(philo, "is eating");
	usleep(data->eat_time * 1000);
	drop_and_take(philo, DROP, data);
	message(philo, "is sleeping");
	usleep(data->sleep_time * 1000);
	philo->eat_cont++;
}

void	*routine(void *struc)
{
	t_data	*data;
	t_philo	philo;
	
	data = (t_data *)struc;
	setting_philo(data, &philo);
	message(&philo, "is created");
	while (philo.eat_cont < data->meals_num)
		eat(data, &philo);
	return (NULL);
}

int	start(t_data *struc)
{
	int	i = 0;

	while (i < struc->num_philo)
	{
		struc->sign_philo = i + 1;
		pthread_create(&struc->tid[i], NULL, &routine, struc);
		usleep(1000);
		i++;
	}
	i = 0;
	while(i < struc->num_philo)
	{
		pthread_join(struc->tid[i], NULL);
		pthread_mutex_destroy(&struc->lock);
		i++;
	}
	return (0);
}


int	main(int argc, char **argv)
{
	t_data	struc;
	
	if (argc < 5 || argc > 6)
		return (0);
	setting_data(&struc, argv);
	start(&struc);
	return (0);
}