
#include "../philo.h"

int	validate_args(int ac, char **av)
{
	int i;
	int j;

	i = 1;
	while(i < ac)
	{
		j = 0;
		while(av[i][j] != '\0')
		{
			if(av[i][j] < '0' || av[i][j] > '9')
			{
				printf("Error: arg '%s' is not a valid positive number\n", av[i]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	resultado;

	i = 0;
	resultado = 0;

	while (str[i])
	{
		resultado = resultado * 10 + (str[i] - '0');
		i++;
	}
	return (resultado);
}