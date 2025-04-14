/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:14:39 by fracurul          #+#    #+#             */
/*   Updated: 2025/04/14 12:24:57 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

//structure for states
typedef enum s_state
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}	t_state;

//Data structure
typedef struct s_data
{
	int		number_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals;
	int		died;
	long	start;
}	t_data;

//Philo structure
typedef struct s_philo
{
	int				id;
	long			d_time;
	long			e_time;
	long			s_time;
	int				needed_meals;
	int				meals_counter;
	long			last_meal;
	long			start;
	int				l_fork;
	int				r_fork;
	int				*died;
	t_state			p_state;
	pthread_t		thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
}	t_philo;

//Atoi
long			ft_atol(const char *str);
int				ft_atoi(const char *str);

//Forks
int				get_right_fork(int id);
int				get_left_fork(int id, int total);
pthread_mutex_t	*init_forks(int philos);
void			free_forks(pthread_mutex_t *forks, int i);

//Performing
int				taking_forks(t_philo *philo);
int				philo_eating(t_philo *philo);
int				philo_sleeping(t_philo *philo);
int				philo_thinking(t_philo *philo);

//Utils
t_data			*init_data(int ac, char **av);
t_philo			*init_data_philo(t_data *p_data, pthread_mutex_t *print_mutex,
					pthread_mutex_t *forks);
long			get_time_ms(void);
char			*get_str_state(t_state state);

//Utils2
pthread_mutex_t	*init_mutex(void);
void			print_philo_state(t_philo *philo, t_state state,
					pthread_mutex_t *print_mutex);
void			init_threads(t_philo *philos, int n_philos);
void			*philo_routine(t_philo *philo);

//Utils3
void			sleep_check(long total_ms, int *died);
int				death_check(t_philo *philo);
void			release_forks(t_philo *philo);
void			*single_routine(t_philo *philo);

//Utils4
int				philo_finished(t_philo *philo, int n);
void			destroy_threads(t_data *data, pthread_mutex_t *forks);

//Validations
int				is_empty(const char *str);
int				validate_num(const char *str);
int				validate_nums(int ac, char **av);
int				validate_philo_range(int n);

//Validations2
int				validate_args(int ac, char **av);
int				validate_meals(int ac, char **av);

#endif