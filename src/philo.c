/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:52:47 by tsurma            #+#    #+#             */
/*   Updated: 2024/06/10 15:21:10 by tsurma           ###   ########.fr       */
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
	while (!tablet->is_dead)
	{
		if (eating(tablet) == -1)
			return (NULL);
		if (--tablet->must_eat == 0)
		{
			tablet->is_dead = 1;
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

// int	check_ded(t_philo *tab)
// {
// 	int	i;

// 	pthread_mutex_unlock(tab->sip);
// 	i = tab->is_dead;
// 	pthread_mutex_lock(tab->sip);
// 	return (i);
// }


void	*hemlock(void *tab)
{
	t_philo	*tablet;

	tablet = (t_philo *)tab;
	while (tablet->rules->is_dead == 0 && tablet->is_dead == 0)
		tablet->is_dead = check_starve(tablet);
	if (tablet->is_dead == -1)
		print_message(DIED, tablet);
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

int	eating(t_philo *tablet)
{
	if (tablet->is_dead != 0)
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
