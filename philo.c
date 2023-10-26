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

void	reset_timer_death(t_philo *philo)
{
	uint64_t	time;

	if (philo->data->one_dead == 1)
		return ;
	time = get_time() - philo->data->start_time;
	philo->time_to_die = time + philo->data->death_time;
	printf("[%ldms] next time death philo %d = %ld\n", time, philo->id_nbr, philo->time_to_die);
}

void	drop_and_take(t_philo *philo, char *info)
{
	if (ft_strcmp(info, TAKE) == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		message(philo, "has taken l fork");
		pthread_mutex_lock(philo->r_fork);
		message(philo, "has taken r fork");
	}
	else if (ft_strcmp(info, DROP) == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		message(philo, "drop l fork");
		pthread_mutex_unlock(philo->r_fork);
		message(philo, "drop r fork");
	}
}

void	eat(t_philo *philo)
{
	if (philo->data->one_dead == 1)
		return ;
	drop_and_take(philo, TAKE);
	pthread_mutex_lock(&philo->lock);
	reset_timer_death(philo);
	message(philo, "is eating");
	// ft_sleep(philo->data->eat_time, philo);
	usleep(philo->data->eat_time * 1000);
	pthread_mutex_unlock(&philo->lock);
	drop_and_take(philo, DROP);
	philo->eat_cont++;
}

void	*routine(void *data_pointer)
{
	t_philo	*philo;
	uint64_t	time;

	philo = (t_philo *)data_pointer;
	time = get_time() - philo->data->start_time;
	philo->time_to_die = time + philo->data->death_time;
	message(philo, "is created");
	while (philo->data->one_dead == 0 && philo->finish == 0)
	{
		eat(philo);
		if (philo->eat_cont == philo->data->meals_nbr)
			philo->finish = 1;
		message(philo, "is sleeping");
		// ft_sleep(philo->data->sleep_time, philo);
		usleep(philo->data->sleep_time * 1000);
		message(philo, "is thinking");
	}
	return (NULL);
}

void	*check_death(void *data_pointer)
{
	uint64_t	time;
	t_philo		*philo;

	philo = (t_philo *)data_pointer;
	while (philo->status == 0)
	{
		time = get_time() - philo->data->start_time;
		if (time > philo->time_to_die)
		{
			message(philo, "is dead");
			philo->status = 1;
			philo->data->one_dead = 1;
			return (NULL);
		}
		if (philo->finish == 1)
		{
			message(philo, "has finished");
			return (NULL);
		}
	}
	return (NULL);
}

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->max_philo)
	{
		pthread_create(&data->tid[i], NULL, &check_death, &data->philo[i]);
		pthread_create(&data->tid[i], NULL, &routine, &data->philo[i]);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < data->max_philo)
	{
		pthread_join(data->tid[i], NULL);
		i++;
	}
	return (0);
}


int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (0);
	set(&data, argc, argv);
	create_thread(&data);
	return (0);
}
