#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

t_condition	*init_set(char **argv)
{
	t_condition	*set;
	int			i;

	i = 0;
	set = (t_condition *)malloc(sizeof(t_condition));
	if (set == NULL)
		return (NULL);
	set->start = get_timestamp();
	set->dead_philo = 0;
	set->num = ft_atoi(argv[1]);
	set->die = ft_atoi(argv[2]);
	set->eat = ft_atoi(argv[3]);
	set->sleep = ft_atoi(argv[4]);
	set->num_of_eat = -1;
	if (argv[5])
		set->num_of_eat = ft_atoi(argv[5]);
	set->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * set->num);
	while (i < set->num && set->forks != NULL)
	{
		if (pthread_mutex_init(&(set->forks)[i], NULL))
			return (NULL);
		i++;
	}
	return (set);
}

t_philo	init_philo(int num, t_condition *set)
{
	t_philo	philo;

	philo.num = num + 1;
	philo.last_eat = set->start;
	philo.left = &(set->forks)[num];
	if (num == 0)
		philo.right = &(set->forks)[set->num - 1];
	else
		philo.right = &(set->forks)[num - 1];
	philo.set = set;
	philo.num_of_eat = set->num_of_eat;
	return (philo);
}

void	clean_data(t_data *set, int philo_amount)
{
	int	i;

	i = 0;
	while (i < philo_amount)
	{
		pthread_mutex_unlock(&(set->set->forks[i]));
		pthread_mutex_destroy(&(set->set->forks[i]));
		i++;
	}
	free(set->threads);
	free(set->philo);
	free(set->set->forks);
	free(set->set);
}
