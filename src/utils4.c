
#include "../philo.h"

t_philo	*init_one_philo(t_data *p_data, pthread_mutex_t *print_mutex, pthread_mutex_t *forks)
{
	int	i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * p_data->number_of_philo);
	if(!philo)
		printf("An error occured alocating memory for the philos");
	while(i < p_data->number_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].d_time = p_data->time_to_die;
		philo[i].e_time = p_data->time_to_eat;
		philo[i].s_time = p_data->time_to_sleep;
		philo[i].needed_meals = p_data->meals;
		philo[i].meals_counter = 0;
		philo[i].start = p_data->start;
		philo[i].last_meal = get_time_ms();
		philo[i].r_fork = get_right_fork(philo[i].id);
		philo[i].died = 0;
		philo[i].p_state = THINKING;
		philo[i].forks = forks;
		i++;
	}
	return (philo);
}

void	one_philo_state(t_philo *philo, t_state state)
{
	long timestamp;

	timestamp = get_time_ms() - philo->start;
	printf("%ld %d %s\n", timestamp, philo->id, get_str_state(state));
}

void	take_fork(t_philo *philo)
{
	if(!death_check(philo) || *philo->died)
		return (0);
	pthread_mutex_lock(&philo->forks[philo->r_fork - 1]);
	print_philo_state(philo, TAKEN_FORK, philo->print_mutex);
	if(!death_check(philo) || *philo->died)
	{
		pthread_mutex_lock(&philo->forks[philo->r_fork - 1]);
		return (0);
	}
	return (1);
}