#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int cnt = 0;
pthread_mutex_t lock;

void* routine(void* arg)
{
	(void)arg;
	pthread_mutex_lock(&lock);
	int i = -1;
	while (++i < 1000)
		cnt++;
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		pthread_t *th;
		int			i;
		int			n_th;
		
		i = 0;
		n_th = atoi(av[1]);
		th = malloc(sizeof(pthread_t)*n_th);
		pthread_mutex_init(&lock,NULL);
		while(i < n_th)
		{
			if(pthread_create(th + i, NULL, &routine, NULL) != 0)
			{
				printf("Error Creating thread n=%d\n",i);
				return 0;
			}
			i++;
			printf("thread %d has started\n",i);
		}
		i = 0;
		while(i < n_th)
		{
			if(pthread_join(th[i],NULL) != 0)
			{
				printf("Error joining thread n=%d\n",i);
				return 0;
			}
			i++;
			printf("thread %d had finished\n",i);
		}
		printf("cnt = %d\n",cnt);
		pthread_mutex_destroy(&lock);
		free(th);
	}
	return 0;
}