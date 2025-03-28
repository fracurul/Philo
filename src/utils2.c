
#include "../philo.h"

pthread_mutex_t	*init_mutex(void)
{
	pthread_mutex_t *mutex;

	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if(mutex == NULL)
	{
		printf("Error alocating memory for mutex");
		return (NULL);
	}
	if(pthread_mutex_init(mutex, NULL) != 0)
	{
		free(mutex);
		printf("Error inicializating mutex");
		return (NULL);
	}
	return (mutex);
}

t_philo	*init_threads(t_philo *philo, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		if(pthread_create(&philo[i].thread, NULL, (void *)philo_routine, &philo[i]) != 0)
		{
			printf("Error creating philo thread");
			return (NULL);
		}
		i++;
	}
	return (philo);
}

void	print_philo_state(int id, t_state state, pthread_mutex_t *print_mutex)
{
	long timestamp;

	timestamp = get_time_ms();
	pthread_mutex_lock(print_mutex);
	printf("%ld %d %s\n", timestamp, id, get_str_state(state));
	pthread_mutex_unlock(print_mutex);
}

void	philo_routine(t_philo *philo)
{
	while(philo->meals_counter < philo->needed_meals || philo->last_meal > 
		philo->d_time)
	{
		pthread_mutex_lock(&philo->forks[philo->l_fork - 1]);
		print_philo_state(philo->id, TAKEN_FORK, philo->print_mutex);
		pthread_mutex_lock(&philo->forks[philo->r_fork - 1]);
		print_philo_state(philo->id, TAKEN_FORK, philo->print_mutex);
		philo->p_state = EATING;
		print_philo_state(philo->id, EATING, philo->print_mutex);
		usleep(get_philo_time(philo->e_time));
		philo->last_meal = get_time_ms();
		philo->meals_counter++;
		pthread_mutex_unlock(&philo->forks[philo->l_fork - 1]);
		pthread_mutex_unlock(&philo->forks[philo->r_fork - 1]);
		philo->p_state = SLEEPING;
		print_philo_state(philo->id, SLEEPING, philo->print_mutex);
		usleep(get_philo_time(philo->s_time));
		philo->p_state = THINKING;
		print_philo_state(philo->id, THINKING, philo->print_mutex);
	}
	print_philo_state(philo->id, DIED, philo->print_mutex);
}