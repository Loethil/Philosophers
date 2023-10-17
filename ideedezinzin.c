#include <pthread.h>
#include <stdio.h>
#include "philo.h"


// Petit fonctionnement des threads et de mutex
int	cont = 0;
pthread_mutex_t lock;

void	*compte()
{
	int	i = -1;

	while (++i < 1000000)
	{
		pthread_mutex_lock(&lock);
		cont++;
		pthread_mutex_unlock(&lock);
	}
	return(NULL);
}

int	main(void)
{
	pthread_t	one;
	pthread_t	two;

	pthread_mutex_init(&lock, NULL);
	pthread_create(&one, NULL, &compte, NULL);
	pthread_create(&two, NULL, &compte, NULL);
	pthread_join(one, NULL);
	pthread_join(two, NULL);
	pthread_mutex_destroy(&lock);
	printf("compt = %d\n", cont);
}

// essai num 1 pour calculer le temps avec gettimepfday
int	main(int argc, char **argv
{
	t_philo	philo1;
	struct	timeval	current_time;
	long long int	time;

	if (argc != 3)
		return (0);
	gettimeofday(&current_time, NULL);
	time = current_time.tv_usec / 1000;
	philo1.status = 0;
	while (philo1.status == 0)
	{
		gettimeofday(&current_time, NULL);
		philo1.horloge = current_time.tv_usec / 1000;
		if(philo1.horloge >= time + 10)
			philo1.status = 1;
		else if (philo1.status == 0)
			printf("philo1 alive and waiting to die at time = %lld ms\n", philo1.horloge);
	}
	printf("philo1 is dead at time = %lld ms \n", philo1.horloge);
	return (0);
}

void	*routine(void *data)
{
	t_data	*stru;

	stru = (t_data *)data;
	return (NULL);
}