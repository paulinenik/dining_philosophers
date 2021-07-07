#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

void	clean_data(t_data *set, int philo_amount)
{
	int	i;

	i = 0;
	while (i >= 0)
	{
		pthread_detach(set->threads[i]);
		i--;
	}
	while (i < philo_amount)
	{
		pthread_mutex_destroy(&(set->set->forks[i]));
		i++;
	}
	free(set->threads);
	free(set->philo);
	free(set->set->forks);
	free(set->set);
}
