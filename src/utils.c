#include <philo.h>

void	exit_philo(t_table *tab, pthread_t *thread_id)
{
	int	i;

	i = -1;
	while (++i < tab->philos_num)
		pthread_join(thread_id[i], NULL);
	i = -1;
	while (++i < tab->philos_num)
		pthread_mutex_destroy(&tab->philos[i].fork);
	pthread_mutex_destroy(&tab->print);
	pthread_mutex_destroy(&tab->check);
	free(tab->philos);
	free(thread_id);
}

size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_wait(t_table *tab, size_t time_to_die)
{
	size_t	t;

	t = get_time();
	while (!(tab->dead))
	{
		if (get_time() - t >= time_to_die)
			break ;
		usleep(100);
	}
}
