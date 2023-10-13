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
	size_t t0;
	pthread_t th;
	t_data	*data;
}t_philo;

typedef struct s_data
{
	int n_philos;
	int t_todie;
	int t_toeat;
	int t_tosleep;
	int n_phntoeat;
	pthread_mutex_t *fork;
	pthread_mutex_t print;
	t_philo *ph;
}t_data;




long long	ft_atoi(char *s);
