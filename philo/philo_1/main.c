#include "philo.h"

t_condition *init_set(char **argv)
{
	t_condition *set;
	int			i;

	i = 0;
	set = (t_condition *)malloc(sizeof(t_condition));
	if (set == NULL)
		return (NULL);
	set->start = get_timestamp();
	set->dead_philo = 0;
	set->philos = ft_atoi(argv[1]);
	set->time_to_die = ft_atoi(argv[2]);
	set->time_to_eat = ft_atoi(argv[3]);
	set->time_to_sleep = ft_atoi(argv[4]);
	g_max = set->philos / 2 + 1;
	set->eating_philos = 0;
	set->num_of_eat = -1;
	pthread_mutex_init(&set->output, NULL);
	if (argv[5])
		set->num_of_eat = ft_atoi(argv[5]);
	set->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 5);
	if (set->forks == NULL)
		return (NULL);
	while (i < set->philos)
	{
		if (pthread_mutex_init(&(set->forks)[i], NULL))
			printf("error\n");
		i++;
	}
	return (set);
}

int g_eating = 0;
int g_dead = 0;

unsigned	get_timestamp(void)
{
	struct timeval tv;
	struct timezone tz;

	if (gettimeofday(&tv, &tz) != 0)
		return (0);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

int	main(int argc, char **argv)
{
	t_condition *set;

	if (argc < 5 || argc > 6)
		printf("Wrong number of arguments. How about another try? :)\n");
	set = init_set(argv);
	check_set(set);
	start_dining(set);
	//free set
	return (0);
}

void	check_set(t_condition *set)
{
	if (set->time_to_die <= 0 || set->time_to_eat <= 0  || set->time_to_sleep <= 0 || set->philos <= 0)
		printf("This is not really possible, you know. Give it another try, friend\n");
}

void	start_dining(t_condition *set)
{
	t_philo		*philo;
	t_data		data;
	pthread_t	*threads;
	int		i;

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
		philo[i].num = i + 1;
		philo[i].eating = 0;
		philo[i].last_eat = set->start;
		philo[i].left = &(set->forks)[i];
		if (i == 0)
			philo[i].right = &(set->forks)[set->philos - 1];
		else
			philo[i].right = &(set->forks)[i - 1];
		philo[i].set = set;
		philo[i].num_of_eat = set->num_of_eat;
		i++;
	}
	data.philo = philo;
	pthread_create(&threads[i], NULL, &check_for_dead, (void *)&data);
	while (i > 0)
	{
		i--;
		pthread_create(&threads[i], NULL, &philo_lifecycle, (void *)&(philo[i]));		
	}
	while (i < set->philos)
		pthread_join(threads[i++], NULL);
}

void	*philo_lifecycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->set->dead_philo != 1 && philo->set->philos != 0)
	{
		philo->set->eating_philos += 1;
		if (philo->num % 2 == 0)
			ft_usleep(10);
		pthread_mutex_lock(philo->right);
		output(philo, right_fork);
		pthread_mutex_lock(philo->left);
		output(philo, left_fork);
		philo->eating = 1;
		if (philo->eating)
		{
			philo->last_eat = get_timestamp();
			output(philo, eat);
			philo->num_of_eat--;
			if (philo->num_of_eat == 0)
				philo->set->philos--;
			ft_usleep(philo->set->time_to_eat);
			philo->eating = 0;
			pthread_mutex_unlock(philo->right);
			pthread_mutex_unlock(philo->left);
			philo->set->eating_philos -= 1;
			output(philo, SLEEP);
			ft_usleep(philo->set->time_to_sleep);
			output(philo, think);
		}
		// printf("eating philos %d\n\n", philo->set->eating_philos);
	}
	return (NULL);
}

void	output(t_philo *philo, int state)
{	
	char	*message[5];

	message[left_fork] = "has taken left fork";
	message[right_fork] = "has taken right fork";
	message[eat] = "is \033[32;1meating\033[0m";
	message[SLEEP] = "is sleeping";
	message[think] = "is \033[35;1mthinking\033[0m";
	if (philo->set->dead_philo != 1 && philo->set->philos > 0)
		printf("%u ms  %d  %s   %d num of philos\n", get_timestamp() - philo->set->start, philo->num, message[state], philo->set->philos);
}

void	*check_for_dead(void *data)
{
	int i;
	int	philo_amount;
	t_data	*set;

	i = 0;
	set = (t_data *)data;
	philo_amount = set->set->philos;
	while(set->set->dead_philo != 1 && set->set->philos != 0)
	{
		if ((get_timestamp() - set->philo[i].last_eat) >= (set->set->time_to_die + 2) && set->set->philos != 0 && set->philo[i].eating != 1)
		{
			set->set->dead_philo = 1;
			pthread_mutex_unlock(set->philo[i].left);
			printf("\033[33;1m%u ms %d dead\n\033[0m", get_timestamp() - set->set->start, i + 1);
			return (NULL);
		}
		i++;
		if (i == philo_amount)
			i = 0;
		ft_usleep(3);
	}
	if (set->set->philos == 0)
		set->set->dead_philo = 1;
	return (NULL);
}

void	ft_usleep(long time)
{
	long t;

	t = get_timestamp();
	while ((get_timestamp() - t) < time)
		usleep(100);
}