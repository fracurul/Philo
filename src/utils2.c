
pthread_mutex_t *init_mutex(void)
{
	pthread_mutex_t *mutex;
	
	mutex = (pthread_mutex_thread *)malloc(sizeof(pthread_mutex_t));
	if(mutex == NULL)
		return(printf("Error alocating memory for mutex"));
	if(pthread_mutex_init(mutex, NULL) !=0)
	{
		free(mutex);
		return(prinf("Error inicializating mutex"));
	}
	return (mutex);
}

void print_philo_state(int id, t_state, state, pthread_mutex_t *print_mutex)
{
	long timestamp;
	
	timestamp = get_time_ms();
	pthread_mutex_lock(print_mutex);
	printf("%ld %d %s\n", timestamp, philo.id, get_str_state(state));
	pthread_mutex_unlock(print_mutex);
}



void philo_routine(void *arg)
{
	printf()
}