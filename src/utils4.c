/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:07:20 by fracurul          #+#    #+#             */
/*   Updated: 2025/04/14 12:08:13 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_finished(t_philo *philo, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (philo[i].meals_counter < philo[i].needed_meals)
			return (0);
		i++;
	}
	return (1);
}

void	destroy_threads(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
