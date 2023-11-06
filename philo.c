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

void	eat(t_philo *philo)
{
	if (philo->data->one_dead == 1)
		return ;
	if (philo->data->max_philo == 1)
		alone(philo);
	else
	{
		drop_and_take(philo, TAKE);
		pthread_mutex_lock(&philo->lock);
		reset_timer_death(philo);
		message(philo, "is eating");
		ft_sleep(philo->data->eat_time, philo);
		pthread_mutex_unlock(&philo->lock);
		drop_and_take(philo, DROP);
		philo->eat_cont++;
	}
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
			message(philo, "died");
			philo->status = 1;
			philo->data->one_dead = 1;
			return (NULL);
		}
		if (philo->finish == 1)
			return (NULL);
	}
	return (NULL);
}

void	*routine(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)data_pointer;
	reset_timer_death(philo);
	while (philo->data->one_dead == 0 && philo->finish == 0)
	{
		eat(philo);
		if (philo->eat_cont == philo->data->meals_nbr)
		{
			philo->finish = 1;
			break ;
		}
		message(philo, "is sleeping");
		ft_sleep(philo->data->sleep_time, philo);
		message(philo, "is thinking");
	}
	return (NULL);
}

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->max_philo)
	{
		pthread_create(&data->tid[i], NULL, &routine, &data->philo[i]);
		usleep(500);
		pthread_create(&data->tideath[i], NULL, &check_death, &data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->max_philo)
	{
		pthread_join(data->tid[i], NULL);
		pthread_join(data->tideath[i++], NULL);
	}
	ft_free(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("not enough or too much arg\n");
		return (0);
	}
	if (set(&data, argc, argv) == 1)
	{
		printf("invalid argument\n");
		return (0);
	}
	create_thread(&data);
	return (0);
}
