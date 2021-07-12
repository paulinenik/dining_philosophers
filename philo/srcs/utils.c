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

void	ft_usleep(t_philo *philo, unsigned int time)
{
	unsigned int	t;

	t = get_timestamp();
	while ((get_timestamp() - t) < time && philo->set->dead_philo != 1)
		usleep(100);
}
