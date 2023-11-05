/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:34:47 by rrakman           #+#    #+#             */
/*   Updated: 2023/11/05 18:08:40 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(int ac, char **av, t_data *data)
{
	data->n_philos = ft_atoi(av[1]);
	data->t_todie = ft_atoi(av[2]);
	data->t_toeat = ft_atoi(av[3]);
	data->t_tosleep = ft_atoi(av[4]);
	if (ac == 6)
		data->n_phntoeat = ft_atoi(av[5]);
	else
		data->n_phntoeat = -2;
}

int	check_input(int ac, char **av)
{
	int	i;

	if (ac == 6)
	{
		if (ft_atoi(av[5]) <= 0)
			return (0);
	}
	i = 1;
	while (i <= 4)
	{
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_max(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				printf("Error! Only Positive Numbers Please\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	if (!check_input(ac, av) || !check_max(ac, av))
	{
		printf("Error! we dont accept zeros (INT_MAX Aswell).\n");
		return (0);
	}
	return (1);
}

void	ft_usleep(unsigned long timetosleep, t_data *data)
{
	size_t	time;
	size_t	last_t;

	timetosleep /= 1000;
	time = get_current_time();
	last_t = get_current_time();
	while (last_t - time < timetosleep)
	{
		last_t = get_current_time();
		pthread_mutex_lock(&data->death);
		if (data->died == 0)
		{
			pthread_mutex_unlock(&data->death);
			usleep(50);
		}
		else
			pthread_mutex_unlock(&data->death);
	}
}
