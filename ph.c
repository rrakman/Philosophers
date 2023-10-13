# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h> 
# include <unistd.h>
# include <stdbool.h>


typedef struct s_arg {
	int 	philo_n;
	int 	t_death;
	int		t_eat;
	int 	t_sleep;
	int 	t_must_eat;
	bool	kill_all;
	int		chhal_mn_philo_chbee;
} t_arg;

typedef struct s_philo {
	int id;
	int count_eat;
	unsigned long start_time;
	pthread_t philo;
	unsigned long last_time;
	pthread_mutex_t forchita;
	pthread_mutex_t *forchita_lisriya;
	t_arg 	*args;
} t_philo;

long long gettime() {
	struct timeval time;

	gettimeofday(&time, NULL);
	return (((long long)time.tv_sec * 1000 + (long long)time.tv_usec / 1000));
}

void	usleep_custom(unsigned long t_to) {
	long long start = gettime();

	while (gettime() - start < t_to)
		usleep(85);
}


void	*routine(void *ptr) {
	t_philo *philo = (t_philo *)ptr;

	while (1) {
		// Thinking Phase
			printf("%lld %d is thinking\n", gettime() - philo->start_time, philo->id);

		// Holding forks
			pthread_mutex_lock(&philo->forchita);
			printf("%lld %d has taken a fork\n", gettime() - philo->start_time, philo->id);
			pthread_mutex_lock(philo->forchita_lisriya);
			printf("%lld %d has taken a fork\n", gettime() - philo->start_time, philo->id);

		// Eating
			printf("%lld %d is eating\n", gettime() - philo->start_time, philo->id);
			philo->last_time = gettime();
			philo->count_eat++;
			usleep_custom(philo->args->t_eat);

		// Sleep
			pthread_mutex_unlock(&philo->forchita);
			pthread_mutex_unlock(philo->forchita_lisriya);
			printf("%lld %d is sleeping\n", gettime() - philo->start_time, philo->id);
			usleep_custom(philo->args->t_sleep);

		if (philo->args->kill_all || (philo->count_eat >= philo->args->t_must_eat && philo->args->t_must_eat != -1)) {
			philo->args->chhal_mn_philo_chbee++;
			break ;
		}
	}
	return (NULL);
}

void	monitor(t_arg *arguments, t_philo *philo) {
	while (true) {
		for (int i = 0; i < arguments->philo_n; i++) {
			if (gettime() - philo[i].last_time >= arguments->t_death) {
				printf("%lld %d died\n", gettime() - philo->start_time, philo->id);
				arguments->kill_all = true;
				return ;
			}
		}
		if (arguments->chhal_mn_philo_chbee == arguments->philo_n)
			return ;
	}
}

int main(int ac, char **av) {
	long long start_time;
	t_arg argument;
	t_philo *philo;

	bzero(&argument, sizeof(t_arg));
	if (ac < 5 || ac > 6) {
		return 1;
	}
	else {
		argument.philo_n = atoi(av[1]);
		argument.t_death = atoi(av[2]);
		argument.t_eat = atoi(av[3]);
		argument.t_sleep = atoi(av[4]);
		argument.t_must_eat = -1;
		if (av[5])
			argument.t_must_eat = atoi(av[5]);
		if (argument.philo_n <= 0 || argument.philo_n > 200 || argument.t_death <= 0 || argument.t_eat <= 0 || argument.t_sleep <= 0
			|| argument.t_must_eat < -1 || argument.t_must_eat == 0)
				return 1;
	}
	philo = (t_philo *)malloc(sizeof(t_philo) * argument.philo_n);
	if (!philo)
		return 1;
	for (int i = 0; i < argument.philo_n; i++) {
		philo[i].id = i + 1;
		pthread_mutex_init(&philo[i].forchita, NULL);
	}

	for (int i = 0; i < argument.philo_n; i++) {
		philo[i].forchita_lisriya = &philo[i + 1 % argument.philo_n].forchita;
		philo[i].args = &argument;
	}
	start_time = gettime();
	for (int i = 0; i < argument.philo_n; i++) {
		pthread_create(&philo[i].philo, NULL, routine, &philo[i]);
		philo[i].last_time = start_time;
		philo[i].start_time = start_time;
		usleep(33);
	}
	monitor(&argument, philo);
	free(philo);
}