/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:52:09 by rrakman           #+#    #+#             */
/*   Updated: 2023/11/05 18:24:45 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					r_fork;
	int					left_fork;
	int					ate_n;
	size_t				t0;
	size_t				last_meal_t;
	pthread_t			th;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					died;
	int					n_philos;
	size_t				t_todie;
	int					t_toeat;
	int					t_tosleep;
	int					n_phntoeat;
	pthread_mutex_t		*fork;
	pthread_mutex_t		print;
	pthread_mutex_t		meals;
	pthread_mutex_t		time;
	pthread_mutex_t		death;
	pthread_mutex_t		last;
	pthread_mutex_t		meal1;
	t_philo				*ph;

}						t_data;

long long				ft_atoi(char *s);
void					ft_usleep(unsigned long timetosleep, t_data *data);
int						check_input(int ac, char **av);
int						check_max(int ac, char **av);
int						check_args(int ac, char **av);
void					data_init(int ac, char **av, t_data *data);

size_t					get_current_time(void);
void					ft_usleep(unsigned long timetosleep, t_data *data);

void					eat(t_philo *philo);
void					think(t_philo *philo);
void					good_sleep(t_philo *philo);
void					*routine(void *ptr);

void					ft_destroy(t_data *data);
