
#include "../philo.h"

int	get_left_fork(int id, int total)
{
	if(id == 1)
		return (total);
	else
		return(id - 1);
}

int	get_right_fork(int id)
{
		return (id);
}

pthread_mutex_t	*init_forks(int philos)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philos);
	if(!forks)
	{
		printf("Error alocating memory for forks\n");
		return (NULL);
	}
	while(i < philos)
	{
		if(pthread_mutex_init(&forks[i], NULL) != 0)
		{
			printf("Error initializating fork mutex at number: %d\n", i);
			free_forks(forks, i);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

void	free_forks(pthread_mutex_t *forks, int i)
{
	int j;

	j = 0;
	while(j < i)
		free(&forks[j++]);
	free(forks);
}
