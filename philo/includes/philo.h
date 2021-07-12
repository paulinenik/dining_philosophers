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
	int				num;
	unsigned int	die;
	unsigned int	sleep;
	unsigned int	eat;
	unsigned int	start;
	int				num_of_eat;
	int				dead_philo;
	pthread_mutex_t	*forks;
}				t_condition;

typedef struct s_philo
{
	int				num;
	int				num_of_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	unsigned int	last_eat;
	t_condition		*set;
}				t_philo;

typedef struct s_data
{
	t_condition	*set;
	t_philo		*philo;
	pthread_t	*threads;
}			t_data;

typedef enum e_state
{
	LEFT_FORK,
	RIGHT_FORK,
	EAT,
	SLEEP,
	THINK
}			t_state;

int				ft_atoi(const char *str);
unsigned int	get_timestamp(void);
t_condition		*init_set(char **argv);
int				start_dining(t_condition *set);
void			*lifecycle(void *data);
void			*check_for_dead(void *data);
void			output(t_philo *philo, int state);
void			ft_usleep(t_philo *philo, unsigned int time);
t_philo			init_philo(int num, t_condition *set);
void			clean_data(t_data *set, int philo_amount);

#endif