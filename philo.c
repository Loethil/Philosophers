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

void	*routine(void *data_pointer)
{
	int	*nmb;

	pthread_mutex_lock(&lock);
	nmb = (int *)data_pointer;
	pthread_mutex_unlock(&lock);
	printf("hello i'm philo number %d\n", *nmb);
	return (NULL);
}

int	yes(t_data *data, char **argv)
{
	int	data_pointer = 0;
	int	i = 0;

	pthread_mutex_init(&data->mutex, NULL);
	data->num_philo = ft_atoi(argv[1]);
	data->tid = malloc(data->num_philo * sizeof(t_data));
	while (i < data->num_philo)
	{
		pthread_create(&data->tid[i], NULL, &routine, &data_pointer);
		pthread_join(data->tid[i], NULL);
		data_pointer++;
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