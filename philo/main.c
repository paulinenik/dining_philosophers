#include "philo.h"

t_condition *init_set(char **argv)
{
	t_condition *set;
	int			num_of_philo;
	int			i;

	set = (t_condition *)malloc(sizeof(set));
	if (set == NULL)
		return (NULL);
	set->start = get_timestamp();
	set->dead_philo = 0;
	set->philos = ft_atoi(argv[1]);
	set->time_to_die = ft_atoi(argv[2]);
	set->time_to_eat = ft_atoi(argv[3]);
	set->time_to_sleep = ft_atoi(argv[4]);
	set->num_of_eat = -1;
	if (argv[5])
		set->num_of_eat = ft_atoi(argv[5]);
	set->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 5);
	if (set->forks == NULL)
		return (NULL);
	while (i < num_of_philo)
	{
		if (pthread_mutex_init(&(set->forks)[i], NULL))
			printf("error\n");
		i++;
	}
	return (set);
}

t_philo	*init_phile(int num)
{
	int	i;
	t_philo *philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * num);
	while ()
}

unsigned	get_timestamp(void)
{
	struct timeval tv;
	struct timezone tz;
	unsigned	timestamp;

	if (gettimeofday(&tv, &tz) != 0)
		return (0);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

int	main(int argc, char **argv)
{
	t_condition *set;

	if (argv < 5 || argc > 6)
		printf("Wrong number of arguments. Try again :)\n");
	set = init_set(argv);
	check_set(set);
	start_dining(set);
	//free set
	return (0);
}

void	check_set(t_condition *set)
{
	if (set->philos < 2)
		printf("Too little philosophers. How about another try?\n");
	if (set->time_to_die <= 0 || set->time_to_eat <= 0  || set <= set->time_to_sleep <= 0)
		printf("This is not really possible, you know. Give it another try, friend\n");
}

void	start_dining(t_condition *set)
{
	t_philo	*philo;
	t_data	data;
	pthread_t	*threads;
	int		i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * set->philos);
	if (philo == NULL)
		printf("Malloc error");
	threads = (pthread_t *)malloc(sizeof(pthread) * set->philos);
	if (threads == NULL)
		printf("Malloc error");
	while (i < set->philos)
	{
		philo[i].num = i + 1;
		philo[i].last_eat = start;
		philo[i].left = &(set->forks)[i];
		if (i == 0)
			philo[i].right = &(set->forks)[set->philos - 1];
		else
			philo[i].right = &(set->forks)[i - 1];
		data.set = set;
		data.philo = philo[i];
		pthread_create(threads[i], NULL, &philo_lifecycle, (void *))
	}
	
}

void	set_forks(t_philo *philo, pthread_mutex_t *forks)
{
	philo->left = forks[philo->num];
	if p
}

void	*philo_lifecycle(void *philo)
{
	philo = (t_philo *)philo;

}