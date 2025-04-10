
#include "../philo.h"

int	main(int ac, char **av)
{
	if (ac <= 4 || ac > 6  || !validate_args(ac, av))
	{
		printf("Error bad input");
		return (0);
	}
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	t_data			*data;

	print_mutex = init_mutex();
	forks = init_forks(ft_atoi(av[1]));
	data = init_data(ac, av);
	philo = init_data_philo(data, print_mutex, forks);
	if(data->number_of_philo == 1)
		pthread_create(&philo[0].thread, NULL, (void *)single_routine, &philo[0]);
	else
		init_threads(philo, data->number_of_philo);
	if(get_str_state(philo->p_state) == NULL)
	{
		printf("Philo state error");
	}
	if(philo == NULL)
	{
		printf("error at threads");
	}
	int i = 0;
	while(1)
	{
		if(*philo[0].died == 1  || philo_finished(philo, data->number_of_philo))
		{
			while (i < data->number_of_philo)
			{
				pthread_join(philo[i].thread, NULL);
				i++;
			}
			break ;
		}
		usleep (1000);
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	pthread_mutex_destroy(print_mutex);
	free(philo);
	free(data);
}
