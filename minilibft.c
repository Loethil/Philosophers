/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:14:55 by mbatteux          #+#    #+#             */
/*   Updated: 2023/10/24 16:14:56 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_atoi(const char *str)
{
	int	o;
	int	res;

	o = 0;
	res = 0;
	while (str[o])
	{
		if (str[o] >= 48 && str[o] <= 57)
			res = res * 10 + str[o++] - '0';
		else
			return (0);
	}
	return (res);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	if (s2[i])
		return (-1);
	return (0);
}

void	ft_free(t_data *data)
{
	free(data->philo);
	free(data->forks);
	free(data->tid);
	free(data->tideath);
}

int	check_data(t_data *data)
{
	if (data->meals_nbr <= 0)
		return (1);
	if (data->max_philo <= 0)
		return (1);
	if (data->death_time <= 0)
		return (1);
	if (data->eat_time <= 0)
		return (1);
	if (data->sleep_time <= 0)
		return (1);
	if (data->start_time <= 0)
		return (1);
	return (0);
}
