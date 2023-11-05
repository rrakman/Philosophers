/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:56:22 by rrakman           #+#    #+#             */
/*   Updated: 2023/11/05 18:51:54 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->ph[i].th, NULL);
		i++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meals);
	pthread_mutex_destroy(&data->meal1);
	pthread_mutex_destroy(&data->time);
	pthread_mutex_destroy(&data->death);
	free(data->fork);
	free(data->ph);
}
