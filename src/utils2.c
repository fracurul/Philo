
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

void init_threads(t_philo *philo, int n_philos)
{
	int	i;

	i = 0;
	philo->data->died = 0;
	printf("philo.died after: %d\n", philo->data->died);
	while (i < n_philos)
	{
		if(pthread_create(&philo[i].thread, NULL, (void *)philo_routine, &philo[i]) != 0)
		{
			printf("Error creating philo thread");
			return ;
		}
		i++;
	}
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
	if((get_time_ms() - philo->last_meal) >= philo->d_time)
	{
		*philo->died = 1;
		print_philo_state(philo, DIED, philo->print_mutex);
		printf("tiempo sin comer:%ld\n", get_time_ms() - philo->last_meal);
		printf("tiempo de muerte: %ld\n", philo->d_time);
		printf("el filo esta muerto?%d\n", *philo->died);
		return (NULL);
	}
	if(philo->id % 2 == 0)
		usleep(100);
	printf("%d\n", philo->data->died);
	while(*philo->died == 0 && philo->meals_counter < philo->needed_meals)
	{
		pthread_mutex_lock(philo->print_mutex);
		printf("id philo: %d tiempo sin comer1: %ld\n", philo->id, (get_time_ms() - philo->last_meal));
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_lock(&philo->forks[philo->l_fork - 1]);
		printf("philo numero: %d, coge el tenedor izq : %d\n", philo->id, philo->l_fork);
		print_philo_state(philo, TAKEN_FORK, philo->print_mutex);
		pthread_mutex_lock(&philo->forks[philo->r_fork - 1]);
		printf("philo numero: %d, coge el tenedor drc: %d\n", philo->id, philo->r_fork);
		print_philo_state(philo, TAKEN_FORK, philo->print_mutex);
		philo->p_state = EATING;
		print_philo_state(philo, EATING, philo->print_mutex);
		usleep(philo->e_time);
		philo->last_meal = (get_time_ms() - philo->last_meal);
		pthread_mutex_lock(philo->print_mutex);
		printf("id philo: %d ultima comida: %ld\n", philo->id, philo->last_meal);
		printf("id philo: %d tiempo de muerte: %ld\n", philo->id, philo->d_time);
		pthread_mutex_unlock(philo->print_mutex);
		philo->meals_counter++;
		pthread_mutex_lock(philo->print_mutex);
		printf("comidas: %d\n", philo->meals_counter);
		printf("comidas necesitadas %d\n", philo->needed_meals);
		pthread_mutex_unlock(philo->print_mutex);
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