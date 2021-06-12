#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_condition
{
	int				philos;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	unsigned		start;
	int				num_of_eat;
	int				eating_philos;
	int				dead_philo;
	pthread_mutex_t *forks;
}				t_condition;

typedef struct	s_philo
{
	int				num;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	suseconds_t last_eat;
}				t_philo;

typedef struct s_data
{
	t_condition *set;
	t_philo		*philo;
}			t_data;


int			ft_atoi(const char *str);
unsigned	get_timestamp(void);

#endif