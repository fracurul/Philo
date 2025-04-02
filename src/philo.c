
#include "../philo.h"

/*int	main(int ac, char **av)
{
	if(ac != 6)
		printf("Error bad input");

	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philosopher;
	t_data			philo_data;

	print_mutex = init_mutex();
	forks = init_forks(ft_atoi(av[1]));
	philo_data = init_data(av);
	philosopher = init_data_philo(philo_data, print_mutex, forks);
	philo_routine(philosopher);
}*/

int	main(int ac, char **av)
{
	if (ac <= 4 || ac > 6 )
	{
		printf("Error bad input");
		return (0);
	}
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	t_data			philo_data;

	print_mutex = init_mutex();
	forks = init_forks(ft_atoi(av[1]));
	philo_data = init_data(ac, av);
	/*printf("numero de filos: %d\n", philo_data.number_of_philo);
	printf("time to die: %d\n", philo_data.time_to_die);
	printf("time to eat: %d\n", philo_data.time_to_eat);
	printf("time to sleep: %d\n", philo_data.time_to_sleep);*/

	philo = init_data_philo(philo_data, print_mutex, forks);
	printf("philo.died in main: %d\n", philo->data->died);
	/*printf("filosofo: %d\n", philo->id);
	printf("time to die: %d\n", philo->d_time);
	printf("time to eat: %d\n", philo->e_time);
	printf("time to sleep: %d\n", philo->s_time);
	printf("meals needed: %d\n", philo->needed_meals);
	printf("meals counter: %d\n", philo->meals_counter);
	printf("last meal: %ld\n", philo->last_meal);
	printf("estado: %s\n", get_str_state(philo->p_state));*/

	init_threads(philo, philo_data.number_of_philo);
	if(get_str_state(philo->p_state) == NULL)
	{
		printf("Philo state error");
	}
	if(philo == NULL)
	{
		printf("error at threads");
	}
	int i = 0;
	while (i < philo_data.number_of_philo)
	{
		printf("llega\n");
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < philo_data.number_of_philo)
	{
		printf("llega1");
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	pthread_mutex_destroy(print_mutex);
	free(philo);
}
