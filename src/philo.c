
#include "../philo.h"

static int	ft_check(t_philo *philo)
{
	if (philo == NULL)
		return(printf("Error: bad data at philo"), 0);
	if (get_str_state(philo->p_state) == NULL)
		return (printf("Philo state is NULL\n"), 0);
	return (1);
}
static void free_rsc(pthread_mutex_t *forks, pthread_mutex_t *mutex, t_philo *philo, t_data *data)
{
	free(forks);
	pthread_mutex_destroy(mutex);
	free(philo);
	free(data);
}
static void	philo_monitor(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
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
}

int	main(int ac, char **av)
{
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	t_data			*data;

	if (ac <= 4 || ac > 6  || !validate_args(ac, av))
		return(printf("Error bad input\n"), 0);

	print_mutex = init_mutex();
	forks = init_forks(ft_atoi(av[1]));
	data = init_data(ac, av);
	philo = init_data_philo(data, print_mutex, forks);
	if(data->number_of_philo == 1)
		pthread_create(&philo[0].thread, NULL, (void *)single_routine, &philo[0]);
	else
		init_threads(philo, data->number_of_philo);
	if(!ft_check(philo))
		return (0);
	philo_monitor(philo, data);

	free_rsc(forks, print_mutex, philo, data);
}
