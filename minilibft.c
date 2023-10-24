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

int	ft_isdigit(int c)
{
	if (c >= 0 && c <= 9)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	o;
	int	res;

	o = 0;
	res = 0;
	while (str[o] && (ft_isdigit(str[o] - '0') == 1))
		res = res * 10 + str[o++] - '0';
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
