/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:52:47 by tsurma            #+#    #+#             */
/*   Updated: 2024/05/23 10:41:37 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_starve(t_philo *tab);
static void	reset_meal(t_philo *tab);

long long	gtod(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

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

void	*socrates(void *clay)
{
	t_philo		*tablet;
	pthread_t	cup;

	tablet = (t_philo *)clay;
	pthread_create(&cup, NULL, &hemlock, tablet);
	pthread_detach(cup);
	reset_meal(tablet);
	if (tablet->nmb_thrd % 2 == 0)
		usleep(200);
	while (!tablet->is_dead)
	{
		if (eating(tablet) == -1)
			break ;
		if (--tablet->must_eat == 0)
		{
			break ;
		}
		if (print_message(SLEEP, tablet) == -1)
			break ;
		usleep(tablet->rules->tme_slp * 1000);
		if (print_message(THINK, tablet) == -1)
			break ;
	}
	return (NULL);
}

void	*hemlock(void *tab)
{
	t_philo	*tablet;

	tablet = (t_philo *)tab;
	while (tablet->rules->is_dead == 0 && tablet->is_dead == 0)
		tablet->is_dead = check_starve(tablet);
	if (tablet->is_dead == -1)
		print_message(DIED, tablet);
	pthread_mutex_unlock(tablet->l_fork);
	pthread_mutex_unlock(tablet->r_fork);
	return (NULL);
}

static int	check_starve(t_philo *tab)
{
	if ((gtod() - tab->last_meal) > tab->rules->tme_die)
		return (-1);
	if (tab->is_dead != 0 || tab->rules->is_dead != 0)
		return (1);
	return (0);
}

static void	reset_meal(t_philo *tab)
{
	tab->last_meal = gtod();
}

int	eating(t_philo *tablet)
{
	if (tablet->is_dead != 0)
		return (-1);
	takeForkies(tablet);
	print_message(EAT, tablet);
	reset_meal(tablet);
	usleep(tablet->rules->tme_eat * 1000);
	pthread_mutex_unlock(tablet->l_fork);
	pthread_mutex_unlock(tablet->r_fork);
	return (0);
}

void takeForkies(t_philo *tablet)
{
		pthread_mutex_lock(tablet->l_fork);
		print_message(FORK, tablet);
		pthread_mutex_lock(tablet->r_fork);
		print_message(FORK, tablet);
}


int	print_message(int mes, t_philo *tablet)
{
	long long		time;

	pthread_mutex_lock(tablet->print);
	if (tablet->rules->is_dead == 1)
	{
		pthread_mutex_unlock(tablet->print);
		return (-1);
	}
	time = gtod() - tablet->rules->start;
	if (mes == DIED && tablet->is_dead == -1)
	{
		printf("%lli %i has died\n", time, tablet->nmb_thrd);
		tablet->rules->is_dead = 1;
	}
	else if (mes == THINK)
		printf("%lli %i is thinking\n", time, tablet->nmb_thrd);
	else if (mes == FORK)
		printf("%lli %i has taken a fork\n", time, tablet->nmb_thrd);
	else if (mes == EAT)
		printf("%lli %i is eating\n", time, tablet->nmb_thrd);
	else if (mes == SLEEP)
		printf("%lli %i is sleeping\n", time, tablet->nmb_thrd);
	pthread_mutex_unlock(tablet->print);
	if (tablet->rules->is_dead != 0)
		return (-1);
	return (0);
}

void	print_struct(t_house *house)
{
	printf("Num of Philo:\t%i\n", house->nmb_philo);
	printf("Time to die:\t%i\n", house->tme_die);
	printf("Time to eat:\t%i\n", house->tme_eat);
	printf("Time to sleep:\t%i\n", house->tme_slp);
	printf("Must eat:\t%i\n", house->tme_must_eat);
}

