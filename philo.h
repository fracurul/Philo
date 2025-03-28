

#ifndef PHILO_H
# define PHILO_H
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef enum s_state
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}t_state;

typedef struct s_data
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int meals;
}t_data;

typedef struct s_philo
{
	int	id;
	int	d_time;
	int	e_time;
	int s_time;
	int needed_meals;
	int meals_counter;
	long last_meal;
	int	l_fork;
	int	r_fork;
	t_state	p_state;
	pthread_t	thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
}t_philo;


//Utils
t_data	init_data(char **av);
t_philo	*init_data_philo(t_data p_data, pthread_mutex_t *print_mutex,  pthread_mutex_t *forks);
long	get_time_ms(void);
char	*get_str_state(t_state state);

//Utils2
pthread_mutex_t	*init_mutex(void);
void			print_philo_state(int id, t_state state, pthread_mutex_t *print_mutex);
t_philo			*init_threads(t_philo *philos, int n_philos);
void			philo_routine(t_philo *philo);

//Utils3
long get_philo_time(int time);

//Forks
pthread_mutex_t *init_forks(int philos);
int				get_right_fork(int id, int total);
int				get_left_fork(int id, int total);
void			free_forks(pthread_mutex_t *forks, int i);

//pthread
pthread_mutex_t	*init_mutex(void);
pthread_mutex_t *init_forks(int philos);

//Atoi
int	ft_check_sign(const char *str, int *i);
int	ft_atoi(const char *str);

#endif