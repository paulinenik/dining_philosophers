#include "philo.h"

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
	set->philos = ft_atoi(argv[1]);
	set->die = ft_atoi(argv[2]);
	set->eat = ft_atoi(argv[3]);
	set->sleep = ft_atoi(argv[4]);
	set->num_of_eat = -1;
	if (argv[5])
		set->num_of_eat = ft_atoi(argv[5]);
	set->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 5);
	if (set->forks == NULL)
		return (NULL);
	while (i++ < set->philos)
	{
		if (pthread_mutex_init(&(set->forks)[i], NULL))
			printf("Error\n");
	}
	return (set);
}

int	main(int argc, char **argv)
{
	t_condition	*set;

	if (argc < 5 || argc > 6)
		printf("Wrong number of arguments. How about another try? :)\n");
	set = init_set(argv);
	if (set->die <= 0 || set->eat <= 0 || set->sleep <= 0 || set->philos <= 0)
		printf("This is not really possible, you know. Give \
			it another try, friend\n");
	start_dining(set);
	//free set
	return (0);
}

void	start_dining(t_condition *set)
{
	t_philo		*philo;
	t_data		data;
	pthread_t	*threads;
	int			i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * set->philos);
	if (philo == NULL)
		printf("Malloc error");
	threads = (pthread_t *)malloc(sizeof(pthread_t) * (set->philos + 1));
	if (threads == NULL)
		printf("Malloc error");
	data.set = set;
	while (i < set->philos)
	{
		philo[i] = init_philo(i, set);
		i++;
	}
	data.philo = philo;
	pthread_create(&threads[i], NULL, &check_for_dead, (void *)&data);
	while (i-- > 0)
		pthread_create(&threads[i], NULL, &lifecycle, (void *)&(philo[i]));
	while (i < set->philos)
		pthread_join(threads[i++], NULL);
}

void	*lifecycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->set->dead_philo != 1 && philo->set->philos != 0)
	{
		if (philo->num % 2 == 0)
			ft_usleep(10);
		pthread_mutex_lock(philo->right);
		output(philo, right_fork);
		pthread_mutex_lock(philo->left);
		output(philo, left_fork);
		philo->last_eat = get_timestamp();
		output(philo, eat);
		philo->num_of_eat--;
		if (philo->num_of_eat == 0)
			philo->set->philos--;
		ft_usleep(philo->set->eat);
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		output(philo, SLEEP);
		ft_usleep(philo->set->sleep);
		output(philo, think);
	}
	return (NULL);
}

void	*check_for_dead(void *data)
{
	int		philo_amount;
	int		i;
	t_data	*set;

	i = 0;
	set = (t_data *)data;
	philo_amount = set->set->philos;
	while (set->set->dead_philo != 1 && set->set->philos != 0)
	{
		if ((get_timestamp() - set->philo[i].last_eat) >= (set->set->die + 2) \
			 && set->set->philos != 0)
		{
			set->set->dead_philo = 1;
			pthread_mutex_unlock(set->philo[i].left);
			printf("\033[33;1m%u ms %d dead\n\033[0m", \
				get_timestamp() - set->set->start, i + 1);
			return (NULL);
		}
		i++;
		if (i == philo_amount)
			i = 0;
		ft_usleep(3);
	}
	return (NULL);
}
