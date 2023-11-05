/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:35:15 by rrakman           #+#    #+#             */
/*   Updated: 2023/11/05 18:19:40 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo(t_data *data)
{
	int		i;
	size_t	time;

	i = 0;
	time = get_current_time();
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&data->time);
		data->ph[i].t0 = time;
		data->ph[i].last_meal_t = time;
		pthread_mutex_unlock(&data->time);
		pthread_create(&data->ph[i].th, NULL, &routine, &data->ph[i]);
		usleep(20);
		i++;
	}
}

void	philo_init(t_data *data)
{
	int	i;

	data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->n_philos);
	i = 0;
	while (i < data->n_philos)
	{
		data->ph[i].id = i + 1;
		pthread_mutex_init(&data->fork[i], NULL);
		data->ph[i].r_fork = i;
		data->ph[i].left_fork = i + 1;
		if (data->ph[i].left_fork >= data->n_philos)
			data->ph[i].left_fork = 0;
		data->ph[i].data = data;
		data->ph[i].ate_n = 0;
		data->died = 0;
		i++;
	}
	data->died = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meals, NULL);
	pthread_mutex_init(&data->time, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->last, NULL);
	pthread_mutex_init(&data->meal1, NULL);
}

int	check(t_data *data, int i, size_t time, size_t ate_n)
{
	if (ate_n == (size_t)data->n_phntoeat + 1 || time > data->t_todie)
	{
		pthread_mutex_lock(&data->death);
		data->died = 1;
		pthread_mutex_unlock(&data->death);
		pthread_mutex_lock(&data->print);
		pthread_mutex_lock(&data->time);
		if (time > data->t_todie)
			printf("%lu %d %s\n", (get_current_time() - data->ph[i].t0),
				data->ph[i].id, "has died");
		pthread_mutex_unlock(&data->time);
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	return (0);
}

void	monitor(t_data *data)
{
	int		i;
	size_t	time;
	size_t	ate_n;

	while (1)
	{
		i = 0;
		while (i < data->n_philos)
		{
			pthread_mutex_lock(&data->last);
			time = get_current_time() - data->ph[i].last_meal_t;
			pthread_mutex_unlock(&data->last);
			pthread_mutex_lock(&data->meal1);
			ate_n = data->ph[i].ate_n;
			pthread_mutex_unlock(&data->meal1);
			if (check(data, i, time, ate_n))
				return ;
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (!check_args(ac, av))
			return (1);
		data_init(ac, av, &data);
		data.ph = (t_philo *)malloc(sizeof(t_philo) * data.n_philos);
		if (!data.ph)
			return (1);
		philo_init(&data);
		create_philo(&data);
		monitor(&data);
		ft_destroy(&data);
	}
	else
		printf("Error\n");
	return (0);
}
