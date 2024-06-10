/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:52:47 by tsurma            #+#    #+#             */
/*   Updated: 2024/06/10 19:52:06 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_starve(t_philo *tab);

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
	t_philo			*tablet;
	pthread_t		cup;

	tablet = (t_philo *)clay;
	pthread_create(&cup, NULL, &hemlock, tablet);
	pthread_detach(cup);
	tablet->last_meal = gtod();
	if (tablet->nmb_thrd % 2 == 0)
		usleep(200);
	while (!check_dead(tablet))
	{
		if (eating(tablet) == -1)
			return (NULL);
		if (--tablet->must_eat == 0)
		{
			set_dead(tablet, 1);
			return (NULL);
		}
		if (print_message(SLEEP, tablet) == -1)
			return (NULL);
		usleep(tablet->rules->tme_slp * 1000);
		if (print_message(THINK, tablet) == -1)
			return (NULL);
	}
	return (NULL);
}

void	set_dead(t_philo *tab, int j)
{
	pthread_mutex_lock(tab->sip);
	tab->is_dead = j;
	pthread_mutex_unlock(tab->sip);
}

int	check_dead(t_philo *tab)
{
	int	i;

	pthread_mutex_lock(tab->sip);
	i = tab->is_dead;
	pthread_mutex_unlock(tab->sip);
	return (i);
}

int	check_dead_all(t_philo *tab)
{
	int	i;

	pthread_mutex_lock(tab->rules->sip_all);
	i = tab->rules->is_dead;
	pthread_mutex_unlock(tab->rules->sip_all);
	return (i);
}

void	set_dead_all(t_philo *tab, int j)
{
	pthread_mutex_lock(tab->rules->sip_all);
	tab->rules->is_dead = j;
	pthread_mutex_unlock(tab->rules->sip_all);
}


void	*hemlock(void *tab)
{
	t_philo	*tablet;
	int		i;

	i = 0;
	tablet = (t_philo *)tab;
	while (check_dead_all(tab) == 0 && i == 0)
	{
		i = check_starve(tablet);
		set_dead(tablet, i);
	}
	if (i == -1)
		print_message(DIED, tablet);
	return (NULL);
}

static int	check_starve(t_philo *tab)
{
	if ((gtod() - tab->last_meal) > tab->rules->tme_die)
		return (-1);
	if (check_dead(tab) != 0 || check_dead_all(tab) != 0)
		return (1);
	return (0);
}

int	eating(t_philo *tablet)
{
	if (check_dead(tablet) != 0)
		return (-1);
	pthread_mutex_lock(tablet->l_fork);
	print_message(FORK, tablet);
	pthread_mutex_lock(tablet->r_fork);
	print_message(FORK, tablet);
	print_message(EAT, tablet);
	tablet->last_meal = gtod();
	usleep(tablet->rules->tme_eat * 1000);
	pthread_mutex_unlock(tablet->l_fork);
	pthread_mutex_unlock(tablet->r_fork);
	return (0);
}
