/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:52:47 by tsurma            #+#    #+#             */
/*   Updated: 2024/05/22 18:05:16 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_starve(t_philo *tab);
static void	reset_meal(t_philo *tab);

int	main(int argc, char **argv)
{
	static t_house	house;

	argc--;
	house.tme_must_eat = -1;
	if (parser(argc, argv, &house) != 0)
		return (EINVAL);
	if (thread_weaver(&house) != 0)
		return (1);
	return (0);
}

void	*plato(void *clay)
{
	t_philo		*tablet;

	tablet = (t_philo *)clay;
	reset_meal(tablet);
	while ((tablet->must_eat)-- != 0)
	{
		if (eating(tablet) == -1)
			return (print_message(DIED, tablet));
		print_message(SLEEP, tablet);
		if (check_starve(tablet) == -1)
			return (print_message(DIED, tablet));
		usleep(tablet->rules->tme_slp * 1000);
		if (check_starve(tablet) == -1)
			return (print_message(DIED, tablet));
		print_message(THINK, tablet);
	}
	return (NULL);
}

static int	check_starve(t_philo *tab)
{
	gettimeofday(&tab->priv, NULL);
	if (((tab->priv.tv_sec * 1000 + tab->priv.tv_usec / 1000)
			- tab->last_meal) > tab->rules->tme_die)
		return (-1);
	return (0);
}

static void	reset_meal(t_philo *tab)
{
	gettimeofday(&tab->priv, NULL);
	tab->last_meal = tab->priv.tv_sec * 1000 + tab->priv.tv_usec / 1000;
}

int	eating(t_philo *tablet)
{
	if (tablet->nmb_thrd % 2)
	{
		pthread_mutex_lock(tablet->l_fork);
		print_message(FORK, tablet);
		pthread_mutex_lock(tablet->r_fork);
		print_message(FORK, tablet);
	}
	else
	{
		pthread_mutex_lock(tablet->r_fork);
		print_message(FORK, tablet);
		pthread_mutex_lock(tablet->l_fork);
		print_message(FORK, tablet);
	}
	if (check_starve(tablet) == -1)
		return (-1);
	reset_meal(tablet);
	print_message(EAT, tablet);
	usleep(tablet->rules->tme_eat * 1000);
	reset_meal(tablet);
	pthread_mutex_unlock(tablet->l_fork);
	pthread_mutex_unlock(tablet->r_fork);
	return (0);
}


void	*print_message(int mes, t_philo *tablet)
{
	long long		time;
	struct timeval	*tv;

	tv = &tablet->priv;
	pthread_mutex_lock(tablet->print);
	gettimeofday(tv, NULL);
	time = (tv->tv_sec * 1000 + tv->tv_usec / 1000) - tablet->rules->start;
	if (mes == THINK)
		printf("%lli %i is thinking\n", time, tablet->nmb_thrd);
	else if (mes == FORK)
		printf("%lli %i has taken a fork\n", time, tablet->nmb_thrd);
	else if (mes == EAT)
		printf("%lli %i is eating\n", time, tablet->nmb_thrd);
	else if (mes == SLEEP)
		printf("%lli %i is sleeping\n", time, tablet->nmb_thrd);
	else
		printf("%lli %i has died\n", time, tablet->nmb_thrd);
	pthread_mutex_unlock(tablet->print);
	return (NULL);
}

void	print_struct(t_house *house)
{
	printf("Num of Philo:\t%i\n", house->nmb_philo);
	printf("Time to die:\t%i\n", house->tme_die);
	printf("Time to eat:\t%i\n", house->tme_eat);
	printf("Time to sleep:\t%i\n", house->tme_slp);
	printf("Must eat:\t%i\n", house->tme_must_eat);
}



