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

pthread_mutex_t	lock;

void	*routine(void *data)
{
	t_data	*stru;

	stru = (t_data *)data;
	pthread_mutex_lock(&lock);
	printf("hello i'm philo number %d\n", stru->sign_philo++);
	// stru->sign_philo = i;
	pthread_mutex_unlock(&lock);
	return (NULL);
}

int	yes(t_data *data, char **argv)
{
	int	i = 0;

	data->sign_philo = 1;
	pthread_mutex_init(&data->mutex, NULL);
	data->num_philo = ft_atoi(argv[1]);
	data->tid = malloc(data->num_philo * sizeof(t_data));
	while (i < data->num_philo)
	{
		pthread_create(&data->tid[i], NULL, &routine, &data);
		pthread_join(data->tid[i], NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc != 5)
		return (0);
	yes(&data, argv);
	return (0);
}