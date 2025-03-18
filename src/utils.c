
#include "philo.h"

t_data init_data(char **av)
{
	t_data p_data;

	p_data.number_of_philo = ft_atoi(av[1]);
	p_data.time_to_die = ft_atoi(av[2]);
	p_data.time_to_eat = ft_atoi(av[3]);
	p_data.time_to_sleep = ft_atoi(av[4]);

	return (p_data);
}

t_philo *init_data_philo(t_data p_data, pthread_mutex_t *print_mutex)
{
	int i;
	t_philo *philo;

	i = 0;
	philo = (philo *)malloc(sizeof(t_philo) * p_data.number_of_philo);
	if(!philo)
		printf("An error occured alocating memory for the philos");
	while(i < p_data.number_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].d_time = p_data.time_to_die;
		philo[i].e_time = p_data.time_to_eat;
		philo[i].s_time = p_data.time_to_sleep;
		philo[i].l_fork = get_left_fork(philo[i].id, p_data.number_of_philo);
		philo[i].r_fork = get_right_fork(philo[i].id, p_data.number_of_philo);
		philo[i].p_state = THINKING;
		philo[i].print_mutex = print_mutex;
		i++;
	}
	return (philo);
}

long get_time_ms(void)
{
	struct timeval time;
	long val;
	long time_ms;

	val = 1000;
	gettimeofday(&time, NULL);
	time_ms = (time.time_sec * val) + (time.time_usec / val);
	return(time_ms);
}

char *get_str_state(t_state state)
{
	if(state == TAKEN_FORK)
		return ("has taken a fork");
	else if(state == EATING)
		return ("is eating");
	else if(state == SLEEPING)
		return ("is sleeping");
	else if(state == THINKING)
		return ("is thinking");
	else if(state == DIED)
		return ("died")
	else
		return ("invalid state")
}
