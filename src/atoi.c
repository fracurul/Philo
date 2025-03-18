
int	ft_check_sign(const char *str, int *i)
{
	int	signo;

	signo = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			signo *= -1;
		*i += 1;
	}
	return (signo);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	resultado;
	int	signo;

	i = 0;
	resultado = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	signo = ft_check_sign(str, &i);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		resultado = resultado * 10 + (str[i] - '0');
		i++;
	}
	return (resultado * signo);
}