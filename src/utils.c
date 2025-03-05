
#include "philo.h"

data init_data(char **av)
{
	data p_data;
	
	p_data.number_of_philo = ft_atoi(av[1]);
	p_data.time_to_die = ft_atoi(av[2]);
	p_data.time_to_eat = ft_atoi(av[3]);
	p_data.time_to_sleep = ft_atoi(av[4]);
	
	return (p_data);
}

philo *init_data_philo(data p_data)
{
	int i;
	philo *philo; 
	
	i = 0;
	philo = (philo *)malloc(sizeof(philo) * p_data.number_of_philo);	
	if(!philo)
		printf("An error occured alocating memory for the philos");
	while(i < p_data.number_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].time_to_die = p_data.time_to_die;
		philo[i].time_to_eat = p_data.time_to_eat;
		philo[i].time_to_sleep = p_data.time_to_sleep;
		philo[i].left_fork = get_left_fork(philo[i].id, p_data.number_of_philo);
		philo[i].right_fork = get_left_fork(philo[i].id, p_data.number_of_philo);
		philo[i].state = THINKING;
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
