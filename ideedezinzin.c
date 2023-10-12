#include <pthread.h>
#include <stdio.h>

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