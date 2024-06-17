/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:52:47 by tsurma            #+#    #+#             */
/*   Updated: 2024/06/17 17:04:16 by tsurma           ###   ########.fr       */
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
	set_last_meal(tablet);
	pthread_mutex_lock(tablet->mute_thread);
	pthread_create(&cup, NULL, &hemlock, tablet);
	pthread_mutex_unlock(tablet->mute_thread);
	usleep(tablet->rules->nmb_philo * 300 - tablet->nmb_thrd * 300);
	set_last_meal(tablet);
	while (tablet->rules->nmb_philo > 1)
	{
		if (eating(tablet) == -1)
			break ;
		if (count_meals(tablet, 1) == -1)
			break ;
		if (print_message(SLEEP, tablet) == -1)
			break ;
		usleep(tablet->rules->tme_slp * 1000);
		if (print_message(THINK, tablet) == -1)
			break ;
	}
	pthread_join(cup, NULL);
	return (NULL);
}

int	count_meals(t_philo *tablet, int i)
{
	if (tablet->rules->tme_must_eat == -1)
		return (0);
	pthread_mutex_lock(tablet->mute_fig);
	tablet->must_eat -= i;
	if (tablet->must_eat == 0)
	{
		pthread_mutex_unlock(tablet->mute_fig);
		return (-1);
	}
	pthread_mutex_unlock(tablet->mute_fig);
	return (0);
}

void	*hemlock(void *tab)
{
	t_philo	*tablet;
	int		i;

	i = 0;
	tablet = (t_philo *)tab;
	while (1)
	{
		pthread_mutex_lock(tablet->mute_death);
		i = tablet->rules->is_dead;
		pthread_mutex_unlock(tablet->mute_death);
		if (i != 0)
			break ;
		if (check_starve(tablet) == -1)
		{
			print_message(DIED, tablet);
			pthread_mutex_lock(tablet->mute_death);
			tablet->rules->is_dead = 1;
			pthread_mutex_unlock(tablet->mute_death);
			break ;
		}
		if (count_meals(tablet, 0) == -1)
			break ;
	}
	return (NULL);
}

static int	check_starve(t_philo *tab)
{
	long long	i;

	pthread_mutex_lock(tab->sip);
	i = gtod() - tab->last_meal;
	pthread_mutex_unlock(tab->sip);
	if (i - 1 > tab->rules->tme_die)
		return (-1);
	return (0);
}
