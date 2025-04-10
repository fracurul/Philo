
#include "../philo.h"

void	sleep_check(long total_ms, int *died)
{
	long start = get_time_ms();
	while((get_time_ms() - start) < total_ms && *died == 0)
	{
		usleep(500);
	}
}

int	death_check(t_philo *philo)
{
	long death_time;

	death_time = get_time_ms() - philo->last_meal;
	if(death_time >= philo->d_time)
	{
		if(*philo->died == 0)
		{
			*philo->died = 1;
			print_philo_state(philo, DIED, philo->print_mutex);
			printf("tiempo sin comer:%ld\n", get_time_ms() - philo->last_meal);
			printf("tiempo de muerte: %ld\n", philo->d_time);
			printf("el filo esta muerto?%d\n", *philo->died);
			return (0);
		}
	}
	return(1);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->l_fork - 1]);
	pthread_mutex_unlock(&philo->forks[philo->r_fork - 1]);
}

void	*single_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[0]);
	print_philo_state(philo, TAKEN_FORK, philo->print_mutex);
	usleep(philo->d_time * 1000);
	pthread_mutex_unlock(&philo->forks[0]);
	print_philo_state(philo, DIED, philo->print_mutex);
	return (NULL);
}