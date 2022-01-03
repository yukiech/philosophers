#include <philo.h>

static int	argv_is_nbr(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		if (argv[i][j] == '-')
			return (1);
		else if (argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
	}
	return (0);
}

static int	argv_is_int(char *s)
{
	size_t	len;
	int	i;

	i = 0;
	len = ft_strlen(s);
	if (s[i] == '+' && s[i + 1])
		len--;
	while (s[i] == '0' && s[i] && len--)
		i++;
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
	if (ft_strncmp(s, "2147483648", 10) >= 0)
		return (1);
	return (0);
}

static int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argv_is_nbr(argc, argv))
		return (1);
	while (i < argc)
	{
		if (argv_is_int(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	initialise_tab(t_table *tab)
{
	int	i;

	tab->dead = 0;
	tab->eaten_all = 0;
	tab->philos = (t_philo *)malloc(tab->philos_num * sizeof(t_philo));
	i = 0;
	while (i < tab->philos_num)
	{
		tab->philos[i].id = i + 1;
		tab->philos[i].tab = tab;
		tab->philos[i].eat_count = 0;
		if (i + 1 == tab->philos_num)
			tab->philos[i].r_philo = &tab->philos[0];
		else
			tab->philos[i].r_philo = &tab->philos[i + 1];
		if (i == 0)
			tab->philos[i].l_philo = &tab->philos[tab->philos_num - 1];
		else
			tab->philos[i].l_philo = &tab->philos[i - 1];
		pthread_mutex_init(&tab->philos[i].fork, NULL);
		i++;
	}
	pthread_mutex_init(&tab->print, NULL);
	pthread_mutex_init(&tab->check, NULL);
}

int	handle_args(int argc, char **argv, t_table *tab)
{
	if (check_args(argc, argv))
		return (1);
	tab->philos_num = ft_atoi(argv[1]);
	tab->die_timer = ft_atoi(argv[2]);
	tab->eat_time = ft_atoi(argv[3]);
	tab->sleep_time = ft_atoi(argv[4]);
	tab->eat_max = -1;
	if (argc == 6)
		tab->eat_max = ft_atoi(argv[5]);
	initialise_tab(tab);
	return (0);
}
