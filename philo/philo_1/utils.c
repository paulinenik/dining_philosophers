#include "philo.h"
#include <stdio.h>

int			ft_atoi(const char *str)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		num = num * 10 + str[i] - 48;
		i++;
	}
	if (str[i] != '\0')
	{
		printf("Wrong arguments. Try again\n");
		return (-1);
	}
	return (num);
}