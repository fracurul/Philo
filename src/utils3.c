
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
	long timestamp;

	death_time = get_time_ms() - philo->last_meal;
	timestamp = get_time_ms() - philo->start;
	if(death_time >= philo->d_time)
	{
		if(*philo->died == 0)
		{
			*philo->died = 1;
			print_philo_state(philo, DIED, philo->print_mutex);
			printf("%ld %d died\n", timestamp, philo->id);
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
	long timestamp;

	timestamp = get_time_ms() - philo->start;
	pthread_mutex_lock(&philo->forks[0]);
	printf("%ld %d has taken a fork\n", timestamp, philo->id);
	usleep(philo->d_time * 1000);
	pthread_mutex_unlock(&philo->forks[0]);
	*philo->died = 1;
	timestamp = get_time_ms() - philo->start;
	printf("%ld %d died\n", timestamp, philo->id);
	return (NULL);
}
