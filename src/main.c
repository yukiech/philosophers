#include <philo.h>

static int	arg_invalide(void)
{
	write(1, "\033[1;31mErreur: arguments invalides\n", 38);
	write(1, "\033[0;33mLes arguments doivent etre des int.\n", 46);
	write(1, "\033[0mUtilisation: ./philo {Nombre de philos} ", 44);
	write(1, "{Duree avant de mourrir} ", 25);
	write(1, "{Duree pour miam} ", 18);
	write(1, "{Duree de dodo} ", 16);
	write(1, "{Nombre de miam necessaire} (optionnel)\n", 40);
	return (EXIT_FAILURE);
}

void	main_toolong(t_table *tab, pthread_t *tid)
{
	check_dead(tab);
	exit_philo(tab, tid);
	write(1, "\033[0;33m\n\n", 10);
	write(1, "##################################################\n", 51);
	write(1, "#                                                #\n", 51);
	write(1, "#               Fin de simulation                #\n", 51);
	write(1, "#                                                #\n", 51);
	write(1, "#                Aucun philosophe                #\n", 51);
	write(1, "#    n'a reelement ete blesse durant les tests   #\n", 51);
	write(1, "#                                                #\n", 51);
	write(1, "##################################################\n", 51);
}

void	print_start()
{
	write(1, "\033[0;33m\n", 9);
	write(1, "##################################################\n", 51);
	write(1, "#                                                #\n", 51);
	write(1, "#              Philosophers Program              #\n", 51);
	write(1, "#                    by ahuber                   #\n", 51);
	write(1, "#                                                #\n", 51);
	write(1, "#             Debut de simulation ...            #\n", 51);
	write(1, "#                                                #\n", 51);
	write(1, "##################################################\n", 51);
	write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	int			i;
	t_table		tab;
	pthread_t	*thread_id;

	if ((argc < 5 || argc > 6) || handle_args(argc, argv, &tab))
		return (arg_invalide());
	thread_id = (pthread_t *)malloc(tab.philos_num * sizeof(pthread_t));
	tab.init_time = get_time();
	i = -1;
	print_start();
	while (++i < tab.philos_num)
	{
		if (pthread_create(&thread_id[i], NULL, &philo_life, &tab.philos[i]))
		{
			write(1, "Erreur: creation de thread impossible\n", 38);
			free(tab.philos);
			free(thread_id);
			return (EXIT_FAILURE);
		}
		pthread_mutex_lock(&tab.check);
		tab.philos[i].last_eat = tab.init_time;
		pthread_mutex_unlock(&tab.check);
	}
	main_toolong(&tab, thread_id);
	return (EXIT_SUCCESS);
}
