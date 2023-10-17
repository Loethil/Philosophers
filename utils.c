/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:08:05 by mbatteux          #+#    #+#             */
/*   Updated: 2023/10/13 15:08:07 by mbatteux         ###   ########.fr       */
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