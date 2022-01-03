#include <philo.h>

void	check_dead(t_table *tab)
{
	int	i;

	while (!tab->eaten_all)
	{
		i = -1;
		while (!tab->dead && ++i < tab->philos_num)
		{
			pthread_mutex_lock(&tab->check);
			if (get_time() - tab->philos[i].last_eat > (size_t)tab->die_timer)
			{
				print_msg(&tab->philos[i], MSG_DEAD);
				tab->dead = 1;
			}
			pthread_mutex_unlock(&tab->check);
			usleep(90);
		}
		if (tab->dead)
			break ;
		i = 0;
		while (tab->eat_max != -1 && i < tab->philos_num
			&& tab->philos[i].eat_count >= tab->eat_max)
			i++;
		if (i == tab->philos_num)
			tab->eaten_all = 1;
	}
}

static void	philo_eat(t_philo *philo)
{
	t_table	*tab;

	tab = philo->tab;
	pthread_mutex_lock(&philo->fork);
	print_msg(philo, MSG_FORK);
	if (philo->tab->philos_num == 1)
	{
		ft_wait(tab, tab->die_timer);
		print_msg(philo, MSG_DEAD);
		pthread_mutex_unlock(&philo->fork);
		tab->dead = 1;
		return ;
	}
	pthread_mutex_lock(&philo->r_philo->fork);
	print_msg(philo, MSG_FORK);
	pthread_mutex_lock(&tab->check);
	philo->eat_count++;
	print_msg(philo, MSG_EAT);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&tab->check);
	ft_wait(tab, tab->eat_time);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->r_philo->fork);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;
	t_table	*tab;

	philo = (t_philo *)arg;
	tab = philo->tab;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!tab->dead && !tab->eaten_all)
	{
		philo_eat(philo);
		print_msg(philo, MSG_SLEEP);
		ft_wait(tab, tab->sleep_time);
		print_msg(philo, MSG_THINK);
	}
	return (NULL);
}
