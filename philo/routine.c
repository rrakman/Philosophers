/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:44:13 by rrakman           #+#    #+#             */
/*   Updated: 2023/11/05 18:20:32 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_print(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->died == 0)
		printf("%lu %d %s\n", (get_current_time() - philo->t0), philo->id, s);
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_unlock(&philo->data->print);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->r_fork]);
	lock_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	lock_print(philo, "has taken a fork");
	lock_print(philo, "is eating");
	ft_usleep(philo->data->t_toeat * 1000, philo->data);
	pthread_mutex_lock(&philo->data->last);
	philo->last_meal_t = get_current_time();
	pthread_mutex_unlock(&philo->data->last);
	pthread_mutex_lock(&philo->data->meal1);
	philo->ate_n++;
	pthread_mutex_unlock(&philo->data->meal1);
	pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
}

void	think(t_philo *philo)
{
	lock_print(philo, "is thinking");
}

void	good_sleep(t_philo *philo)
{
	lock_print(philo, "is sleeping");
	ft_usleep(philo->data->t_tosleep * 1000, philo->data);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 != 0)
	{
		think(philo);
		ft_usleep(philo->data->t_toeat * 1000, philo->data);
	}
	if (philo->id % 2 != 0 && philo->id == philo->data->n_philos)
		good_sleep(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->died)
		{
			pthread_mutex_unlock(&philo->data->death);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->death);
		eat(philo);
		good_sleep(philo);
		think(philo);
	}
	return (NULL);
}
