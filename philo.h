#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>
#include<pthread.h>
#include <sys/time.h>


typedef struct s_data t_data;

typedef struct s_philo
{
	int id;
	int r_fork;
	int left_fork;
	int ate_n;
	size_t t0;
	size_t last_meal_t;
	pthread_t th;
	t_data	*data;
}t_philo;

typedef struct s_data
{
	int died;
	int n_philos;
	size_t t_todie;
	int t_toeat;
	int t_tosleep;
	int n_phntoeat;
	pthread_mutex_t *fork;
	pthread_mutex_t print;
	pthread_mutex_t meals;
	pthread_mutex_t time;
	pthread_mutex_t death;
	t_philo *ph;
}t_data;




long long	ft_atoi(char *s);
void	ft_usleep(unsigned long timetosleep);
