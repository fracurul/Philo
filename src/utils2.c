
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

void	print_philo_state(t_philo *philo, t_state state, pthread_mutex_t *print_mutex)
{
	long timestamp;

	timestamp = get_time_ms() - philo->start;
	pthread_mutex_lock(print_mutex);
	printf("%ld %d %s\n", timestamp, philo->id, get_str_state(state));
	pthread_mutex_unlock(print_mutex);
}

void	*philo_routine(t_philo *philo)
{
	if(philo->last_meal < philo->d_time)
	{
		print_philo_state(philo, DIED, philo->print_mutex);
		return (NULL);
	}
	if(philo->id % 2 == 0)
		usleep(100);
	while(philo->meals_counter < philo->needed_meals)
	{
		pthread_mutex_lock(&philo->forks[philo->l_fork - 1]);
		printf("philo numero: %d, coge el tenedor izq : %d\n", philo->id, philo->l_fork);
		print_philo_state(philo, TAKEN_FORK, philo->print_mutex);
		pthread_mutex_lock(&philo->forks[philo->r_fork - 1]);
		printf("philo numero: %d, coge el tenedor drc: %d\n", philo->id, philo->r_fork);
		print_philo_state(philo, TAKEN_FORK, philo->print_mutex);
		philo->p_state = EATING;
		print_philo_state(philo, EATING, philo->print_mutex);
		usleep(philo->e_time);
		philo->last_meal = get_time_ms();
		philo->meals_counter++;
		printf("comidas: %d\n", philo->meals_counter);
		printf("comidas necesitadas %d\n", philo->needed_meals);
		pthread_mutex_unlock(&philo->forks[philo->l_fork - 1]);
		pthread_mutex_unlock(&philo->forks[philo->r_fork - 1]);
		philo->p_state = SLEEPING;
		print_philo_state(philo, SLEEPING, philo->print_mutex);
		usleep(philo->s_time);
		philo->p_state = THINKING;
		print_philo_state(philo, THINKING, philo->print_mutex);
	}
	return (NULL);
}