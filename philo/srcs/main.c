#include "philo.h"

int	main(int argc, char **argv)
{
	t_condition	*set;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments. How about another try? :)\n");
		return (1);
	}
	set = init_set(argv);
	if (set == NULL || set->forks == NULL)
	{
		printf("Error\n");
		free(set);
		return (1);
	}
	if (set->die <= 0 || set->eat <= 0 || set->sleep <= 0 || set->num <= 0)
	{
		printf("This is not really possible, you know. ");
		printf("Give it another try, friend\n");
		return (1);
	}
	if (start_dining(set) == 1)
		return (1);
	return (0);
}

int	start_dining(t_condition *set)
{
	t_philo		*philo;
	t_data		data;
	pthread_t	*threads;
	int			i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * set->num);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * (set->num + 1));
	if (threads == NULL || threads == NULL)
	{
		printf("Malloc error");
		return (1);
	}
	while (++i < set->num)
		philo[i] = init_philo(i, set);
	data.set = set;
	data.philo = philo;
	data.threads = threads;
	pthread_create(&threads[i], NULL, &check_for_dead, (void *)&data);
	while (i-- > 0)
		pthread_create(&threads[i], NULL, &lifecycle, (void *)&(philo[i]));
	while (i < set->num)
		pthread_join(threads[i++], NULL);
	return (0);
}

void	*lifecycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->num % 2 == 0)
		usleep(100);
	while (philo->set->dead_philo != 1 && philo->set->num > 0)
	{
		pthread_mutex_lock(philo->right);
		output(philo, RIGHT_FORK);
		pthread_mutex_lock(philo->left);
		output(philo, LEFT_FORK);
		output(philo, EAT);
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		output(philo, SLEEP);
		output(philo, THINK);
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
	philo_amount = set->set->num;
	while (set->set->dead_philo != 1 && set->set->num > 0)
	{
		if ((get_timestamp() - set->philo[i].last_eat) >= set->set->die \
			 && set->set->num > 0)
		{
			set->set->dead_philo = 1;
			pthread_mutex_unlock(set->philo[i].left);
			printf("\033[33;1m%u ms %d dead\n\033[0m", \
				get_timestamp() - set->set->start, i + 1);
		}
		i++;
		if (i == philo_amount)
			i = 0;
		usleep(2 * 1000);
	}
	usleep(600 * 1000);
	clean_data(set, philo_amount);
	return (NULL);
}

void	output(t_philo *philo, int state)
{
	char	*message[5];

	message[LEFT_FORK] = "has taken left fork";
	message[RIGHT_FORK] = "has taken right fork";
	message[EAT] = "is \033[32;1meating\033[0m";
	message[SLEEP] = "is sleeping";
	message[THINK] = "is \033[35;1mthinking\033[0m";
	if (state == EAT)
		philo->last_eat = get_timestamp();
	if (philo->set->dead_philo != 1 && philo->set->num > 0)
		printf("%u ms  %d  %s\n", get_timestamp() - philo->set->start, \
			philo->num, message[state]);
	if (state == EAT && philo->set->dead_philo != 1)
	{
		philo->num_of_eat--;
		if (philo->num_of_eat == 0)
			philo->set->num--;
		ft_usleep(philo, philo->set->eat);
	}
	if (state == SLEEP && philo->set->dead_philo != 1)
		ft_usleep(philo, philo->set->sleep);
}
