
#include "../philo.h"

int validate_meals(int ac, char **av)
{
	long meals;

	if(ac == 6)
	{
		meals = ft_atol(av[5]);
		if(meals <= 0 || meals > INT_MAX)
		{
			printf("Error: nº of meals must be positive and at most INT_MAX.\n");
			return (0);
		}
	}
	return (1);
}

int	validate_args(int ac, char **av)
{
	int i;
	int num;

	i = 1;
	while (i < ac)
	{
		if (!validate_nums(ac, av))
		{
			printf("Error: arg '%s' is not a valid positive number.\n", av[i]);
			return (0);
		}
		i++;
	}
	num = ft_atoi(av[1]);
	if (!validate_philo_range(num))
		return (0);
	if (!validate_meals(ac, av))
		return (0);
	return (1);
}