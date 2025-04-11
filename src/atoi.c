
#include "../philo.h"

long	ft_atol(const char *str)
{
	int i;
	long res;

	i = 0;
	res = 0;
	while(str[i] != '\0')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
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
