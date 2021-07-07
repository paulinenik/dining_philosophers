#include "philo.h"
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		num = num * 10 + str[i] - 48;
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (num);
}

unsigned int	get_timestamp(void)
{
	struct timeval	value;
	struct timezone	zone;
	int				status;

	status = gettimeofday(&value, &zone);
	if (status != 0)
		return (0);
	return (value.tv_usec / 1000 + value.tv_sec * 1000);
}

void	ft_usleep(unsigned int time)
{
	unsigned int	t;

	t = get_timestamp();
	while ((get_timestamp() - t) < time)
		usleep(100);
}

void	output(t_philo *philo, int state)
{
	char	*message[5];

	message[LEFT_FORK] = "has taken left fork";
	message[RIGHT_FORK] = "has taken right fork";
	message[EAT] = "is \033[32;1meating\033[0m";
	message[SLEEP] = "is sleeping";
	message[THINK] = "is \033[35;1mthinking\033[0m";
	if (philo->set->dead_philo != 1 && philo->set->num > 0)
		printf("%u ms  %d  %s\n", get_timestamp() - philo->set->start, \
			philo->num, message[state]);
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
