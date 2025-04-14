/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:55:28 by fracurul          #+#    #+#             */
/*   Updated: 2025/04/14 12:05:43 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_mutex_t	*init_mutex(void)
{
	pthread_mutex_t	*mutex;

	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
	{
		printf("Error alocating memory for mutex");
		return (NULL);
	}
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		free(mutex);
		printf("Error inicializating mutex");
		return (NULL);
	}
	return (mutex);
}

void	init_threads(t_philo *philo, int n_philos)
{
	int	i;

	i = 0;
	*philo->died = 0;
	while (i < n_philos)
	{
		if (pthread_create(&philo[i].thread, NULL,
				(void *)philo_routine, &philo[i]) != 0)
		{
			printf("Error creating philo thread");
			return ;
		}
		i++;
	}
}

void	print_philo_state(t_philo *philo, t_state state,
	pthread_mutex_t *print_mutex)
{
	long	timestamp;

	pthread_mutex_lock(print_mutex);
	if (!death_check(philo) || *philo->died)
	{
		pthread_mutex_unlock(print_mutex);
		return ;
	}
	timestamp = get_time_ms() - philo->start;
	if (!death_check(philo) || *philo->died)
	{
		pthread_mutex_unlock(print_mutex);
		return ;
	}
	printf("%ld %d %s\n", timestamp, philo->id, get_str_state(state));
	pthread_mutex_unlock(print_mutex);
}

void	*philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(100);
	while (*philo->died == 0 && philo->meals_counter < philo->needed_meals)
	{
		if (!death_check(philo) || *philo->died)
			return (NULL);
		if (!taking_forks(philo))
			return (NULL);
		if (!philo_eating(philo))
		{
			release_forks(philo);
			return (NULL);
		}
		release_forks(philo);
		if (!philo_sleeping(philo))
			return (NULL);
		if (!philo_thinking(philo))
			return (NULL);
	}
	return (NULL);
}
