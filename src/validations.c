
#include "../philo.h"

int	is_empty(const char *str)
{
	if(str == NULL || str[0] == '\0')
		return (1);
	return (0);
}

int	validate_num(const char *str)
{
	int i;

	i = 0;
	if (is_empty(str))
		return (0);
	if (str[0] == '-' || str[0] == '+')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	validate_nums(int ac, char **av)
{
	int i;

	i = 1;
	if(is_empty(av[i]))
		return (0);
	while (i < ac)
	{
		if (!validate_num(av[i]))
		{
			printf("Error: arg %s is empty or not a valid number\n", av[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_philo_range(int n)
{
	if (n < 1 || n > 200)
	{
		printf("Error: nº of philosophers must be between 1 and 200.\n");
		return (0);
	}
	return (1);
}

