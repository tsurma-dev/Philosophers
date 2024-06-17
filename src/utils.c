/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:11:48 by tsurma            #+#    #+#             */
/*   Updated: 2024/06/17 17:06:31 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	take_forks(t_philo *tablet);

long long	gtod(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	print_message(int mes, t_philo *tablet)
{
	long long		time;
	static int		i;

	pthread_mutex_lock(tablet->print);
	if (i != 0)
	{
		pthread_mutex_unlock(tablet->print);
		return (-1);
	}
	time = gtod() - tablet->rules->start;
	if (mes == DIED)
	{
		printf("%lli %i has died\n", time, tablet->nmb_thrd);
		i = 1;
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
	return (0);
}

void	set_last_meal(t_philo *tablet)
{
	pthread_mutex_lock(tablet->sip);
	tablet->last_meal = gtod();
	pthread_mutex_unlock(tablet->sip);
}

int	eating(t_philo *tablet)
{
	int	i;

	pthread_mutex_lock(tablet->mute_death);
	i = tablet->rules->is_dead;
	pthread_mutex_unlock(tablet->mute_death);
	if (i != 0)
		return (-1);
	take_forks(tablet);
	print_message(EAT, tablet);
	set_last_meal(tablet);
	usleep(tablet->rules->tme_eat * 1000);
	pthread_mutex_unlock(tablet->l_fork);
	pthread_mutex_unlock(tablet->r_fork);
	return (0);
}

static void	take_forks(t_philo *tablet)
{
	if (tablet->nmb_thrd % 2 == 0)
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
}
