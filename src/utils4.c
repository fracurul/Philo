
#include "../philo.h"

int	philo_finished(t_philo *philo, int n)
{
	int i;

	i = 0;
	while(i < n)
	{
		if(philo[i].meals_counter < philo[i].needed_meals)
			return (0);
		i++;
	}
	return (1);
}