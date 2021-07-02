#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

int g_max;

typedef struct s_condition
{
	int				philos;
	unsigned		time_to_die;
	unsigned		time_to_sleep;
	unsigned		time_to_eat;
	unsigned		start;
	int				num_of_eat;
	int				eating_philos;
	int				dead_philo;
	pthread_mutex_t	output;
	pthread_mutex_t *forks;
}				t_condition;

typedef struct	s_philo
{
	int			num;
	int			eating;
	int			num_of_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	unsigned last_eat;
	t_condition	*set;
}				t_philo;

typedef struct s_data
{
	t_condition *set;
	t_philo		*philo;
}			t_data;

typedef enum e_state
{
	left_fork, 
	right_fork,
	eat, 
	SLEEP,
	think
}			e_state;

int			ft_atoi(const char *str);
unsigned	get_timestamp(void);
t_condition *init_set(char **argv);
void	check_set(t_condition *set);
void	start_dining(t_condition *set);
void	*philo_lifecycle(void *data);
void	*check_for_dead(void *data);
void	output(t_philo *philo, int state);
void	ft_usleep(long time);

#endif