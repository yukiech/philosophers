#include <philo.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *str1, const char *str2, size_t len)
{
	while (len > 0 && *str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
			break ;
		str1++;
		str2++;
		len--;
	}
	if (len == 0)
		return (0);
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

int	skipspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const	char *str)
{
	int	result;
	int	sign;
	int	int_len;

	result = 0;
	sign = 1;
	int_len = 0;
	while (skipspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = (result * 10) + (*str++ - '0');
		int_len++;
	}
	if (int_len > 10 && sign == 1)
		return (-1);
	else if (int_len > 10)
		return (0);
	return (result * sign);
}
