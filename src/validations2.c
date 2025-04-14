/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:09:11 by fracurul          #+#    #+#             */
/*   Updated: 2025/04/14 12:13:58 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	validate_meals(int ac, char **av)
{
	long	meals;

	if (ac == 6)
	{
		meals = ft_atol(av[5]);
		if (meals <= 0 || meals > INT_MAX)
			return (0);
	}
	return (1);
}

int	validate_args(int ac, char **av)
{
	int	num;

	if (!validate_nums(ac, av))
		return (0);
	num = ft_atoi(av[1]);
	if (!validate_philo_range(num))
		return (0);
	if (!validate_meals(ac, av))
		return (0);
	return (1);
}
