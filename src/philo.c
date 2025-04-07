
#include "../philo.h"

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
	t_data			*philo_data;

	print_mutex = init_mutex();
	forks = init_forks(ft_atoi(av[1]));
	philo_data = init_data(ac, av);
	philo = init_data_philo(philo_data, print_mutex, forks);
	init_threads(philo, philo_data->number_of_philo);
	if(get_str_state(philo->p_state) == NULL)
	{
		printf("Philo state error");
	}
	if(philo == NULL)
	{
		printf("error at threads");
	}
	while(1)
	{
		if(*philo[0].died == 1)
			break;
		usleep (1000);
	}
	int i = 0;
	while (i < philo_data->number_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < philo_data->number_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	pthread_mutex_destroy(print_mutex);
	free(philo);
	free(philo_data);
}
