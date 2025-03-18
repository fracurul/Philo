
#include "philo.h"

int	main(int ac, char **av)
{
	if(ac != 6)
		printf("Error bad input");

	pthread_mutex_t *print_mutex;
	pthread_mutex_t *forks;
	t_philo			*philosopher;
	t_data			philo_data;
	
	print_mutex = init_mutex;
	forks =	init_fork(ft_atoi(av[1]));
	philo_data = init_data(av);
	philosopher = init_data_philo(philo_data, print_mutex, forks);
}