	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   philo.c                                            :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: ta9ra9 <ta9ra9@student.42.fr>              +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2023/09/07 15:22:45 by ta9ra9            #+#    #+#             */
	/*   Updated: 2023/10/13 06:37:48 by ta9ra9           ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#include "philo.h"

	int check_input(int ac, char **av)
	{
		int i;

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

	int check_max(int ac, char **av)
	{
		int i;

		i = 1;
		while (i < ac)
		{
			if (ft_atoi(av[i]) > INT_MAX)
				return (0);
			i++;
		}
		return (1);
	}

	int check_args(int ac, char **av)
	{
		int i;
		int j;

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

	size_t get_current_time(void)
	{
		struct timeval time;
		gettimeofday(&time, NULL);
		return (time.tv_sec * 1000 + time.tv_usec / 1000);
	}

	void data_init(int ac, char **av, t_data *data)
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

	void lock_print(t_philo *philo, char *s)
	{
		pthread_mutex_lock(&philo->data->print);
		pthread_mutex_lock(&philo->data->time);
		printf("%lu %d %s\n", (get_current_time() - philo->t0), philo->id, s);
		pthread_mutex_unlock(&philo->data->time);
		pthread_mutex_unlock(&philo->data->print);
	}

	void	eat(t_philo *philo)
	{
		pthread_mutex_lock(&philo->data->fork[philo->r_fork]);
		lock_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
		lock_print(philo, "has taken a fork");
		lock_print(philo, "is eating");
		ft_usleep(philo->data->t_toeat * 1000);
		pthread_mutex_lock(&philo->data->meals);
		philo->last_meal_t = get_current_time();
		philo->ate_n++;
		pthread_mutex_unlock(&philo->data->meals);
		pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
	}

	void think(t_philo *philo)
	{
		lock_print(philo, "is thinking");
	}

	void good_sleep(t_philo *philo)
	{
		lock_print(philo, "is sleeping");
		ft_usleep(philo->data->t_tosleep * 1000);
	}

	void *routine(void *ptr)
	{
		t_philo *philo = (t_philo *)ptr;
		if(philo->id % 2 != 0)
		{
			think(philo);
			ft_usleep(philo->data->t_toeat * 1000);
		}
		if(philo->id % 2 != 0 && philo->id == philo->data->n_philos)
				good_sleep(philo);
		while(1)
		{
			pthread_mutex_lock(&philo->data->death);
			if(philo->data->died)
			{
				pthread_mutex_unlock(&philo->data->death);
				return NULL;
			}
			pthread_mutex_unlock(&philo->data->death);
			eat(philo);
			good_sleep(philo);
			think(philo);
		}
		return NULL;
	}

	void	create_philo(t_data *data)
	{
		int i = 0;
		size_t time = get_current_time();
		while(i < data->n_philos)
		{
			pthread_mutex_lock(&data->time);
			data->ph[i].t0 = get_current_time();
			data->ph[i].last_meal_t = time;
			pthread_mutex_unlock(&data->time);
			pthread_create(&data->ph[i].th,NULL,&routine,&data->ph[i]);
			usleep(20);
			i++;
		}
	}

	void philo_init(t_data *data)
	{
		data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->n_philos);
		int i = 0;
		while (i < data->n_philos)
		{
			data->ph[i].id = i + 1;
			pthread_mutex_init(&data->fork[i],NULL);
			data->ph[i].r_fork = i;
			data->ph[i].left_fork = i+1;
			if(data->ph[i].left_fork >= data->n_philos)
				data->ph[i].left_fork = 0;
			data->ph[i].data = data;
			data->ph[i].ate_n = 0;
			data->died = 0;
			i++;
		}
		data->died = 0;
		pthread_mutex_init(&data->print,NULL);
		pthread_mutex_init(&data->meals, NULL);
		pthread_mutex_init(&data->time, NULL);
		pthread_mutex_init(&data->death, NULL);
	}

	void	ft_usleep(unsigned long timetosleep)
	{
		timetosleep /= 1000;
		size_t time = get_current_time();
		size_t last_t = get_current_time();

		while(last_t - time < timetosleep)
		{
			last_t = get_current_time();
			usleep(150);
		}
	}

	void	monitor(t_data *data)
	{
		int i = 0;
		while(1)
		{
			i = 0;
			while(i < data->n_philos)
			{
				pthread_mutex_lock(&data->meals);
				size_t time = get_current_time() - data->ph[i].last_meal_t ;
				if(data->ph[i].ate_n == data->n_phntoeat + 	1 || time > data->t_todie)
				{
					data->died = 1;
					pthread_mutex_lock(&data->print);
					if( time > data->t_todie)
						printf("%lu %d %s\n", (get_current_time() - data->ph[i].t0),data->ph[i].id, "has died");
					pthread_mutex_unlock(&data->meals);
					return;
				}
				pthread_mutex_unlock(&data->meals);
				i++;
			}	
		}
	}

	int main(int ac, char **av)
	{
		t_data data;
		
		if (ac == 5 || ac == 6)
		{
			if (!check_args(ac, av))
				return (1);
			data_init(ac, av, &data);
			data.ph = (t_philo *)malloc(sizeof(t_philo) * data.n_philos);
			if (!data.ph)
				return 1;
			philo_init(&data);
			create_philo(&data);
			monitor(&data);
			pthread_mutex_destroy(&data.print);
        	pthread_mutex_destroy(&data.meals);
        	pthread_mutex_destroy(&data.time);
        	pthread_mutex_destroy(&data.death);
			free(data.fork);
			free(data.ph);
		}
		else
			printf("Error\n");
		return (0);
	}
