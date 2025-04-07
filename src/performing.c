
#include "../philo.h"

int	taking_forks(t_philo *philo)
{
	if(!death_check(philo) || *philo->died)
		return (0);
	pthread_mutex_lock(&philo->forks[philo->l_fork - 1]);
	print_philo_state(philo, TAKEN_FORK, philo->print_mutex);
	if(!death_check(philo) || *philo->died)
	{
		pthread_mutex_unlock(&philo->forks[philo->l_fork - 1]);
		return (0);
	}
	pthread_mutex_lock(&philo->forks[philo->r_fork - 1]);
	//print_philo_state(philo, TAKEN_FORK, philo->print_mutex);
	if(!death_check(philo) || *philo->died)
	{
		pthread_mutex_unlock(&philo->forks[philo->l_fork - 1]);
		pthread_mutex_unlock(&philo->forks[philo->r_fork - 1]);
		return (0);
	}
	return (1);
}

int	philo_eating(t_philo *philo)
{
	if(!death_check(philo) || *philo->died)
		return (0);
	philo->p_state = EATING;
	print_philo_state(philo, EATING, philo->print_mutex);
	sleep_check(philo->e_time, 1, philo->died);
	if(!death_check(philo) || *philo->died)
		return (0);
	philo->last_meal = get_time_ms();
	philo->meals_counter++;
	return (1);
}

int	philo_sleeping(t_philo *philo)
{
	if(!death_check(philo) || *philo->died)
		return (0);
	philo->p_state = SLEEPING;
	print_philo_state(philo, SLEEPING, philo->print_mutex);
	sleep_check(philo->s_time, 1, philo->died);
	return (!(*philo->died));
}

int	philo_thinking(t_philo *philo)
{
	if(!death_check(philo) || *philo->died)
		return (0);
	philo->p_state = THINKING;
	print_philo_state(philo, THINKING, philo->print_mutex);
	return (1);
}