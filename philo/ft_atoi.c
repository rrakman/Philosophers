/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:35:01 by rrakman           #+#    #+#             */
/*   Updated: 2023/11/05 17:51:46 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(char *s)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (s[i] == ' ' || (s[i] >= 8 && s[i] <= 13))
		i++;
	while (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res * sign);
}
