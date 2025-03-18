
#include "philo.h"

int	main(int ac, char **av)
{
	if(ac != 5)
		printf("Error bad input");

	data philo_data;
	philo *philosopher;

	philo_data = init_data(av);
	philosopher = init_data_philo(philo_data);
}