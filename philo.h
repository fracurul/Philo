************************************************************************* */

#ifndef PHILO_H
# define PHILO_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int left_fork;
	int right_fork;
	t_state	state;
}data;

typedef struct s_philo
{
	int	id;
	int	d_time;
	int	e_time;
	int s_time;
}philo;

tydef enum e_state
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}t_state;


//Utils
data	init_data(char **av);
philo	*init_data_philo(data p_data);
long	get_time_ms(void);
char	*get_str_state(t_state state);

//Utils2

//Atoi
int	ft_check_sign(const char *str, int *i);
int	ft_atoi(const char *str);

//pthread
pthread_mutex_t print_mutex;

#endif