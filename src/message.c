#include <philo.h>

static char	*get_msg(int msg)
{
	if (msg == MSG_FORK)
		return ("\033[1;33mhas taken a fork");
	if (msg == MSG_EAT)
		return ("\033[1;32mis eating");
	if (msg == MSG_SLEEP)
		return ("\033[1;34mis sleeping");
	if (msg == MSG_THINK)
		return ("\033[1;36mis thinking");
	if (msg == MSG_DEAD)
		return ("\033[1;31mdied");
	return("Error");
}

void	print_msg(t_philo *philo, int msg)
{
	size_t	t;

	t = get_time() - philo->tab->init_time;
	pthread_mutex_lock(&philo->tab->print);
	if (!philo->tab->dead && !philo->tab->eaten_all)
	{
		printf("\033[1;90m%3ld ms ", t);
		printf("\033[1;33m%d ", philo->id);
		printf("%s", get_msg(msg));
		if (msg == MSG_EAT)
			printf(" #%d", philo->eat_count);
		printf("\n");
	}
	pthread_mutex_unlock(&philo->tab->print);
}
