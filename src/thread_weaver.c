/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_weaver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:55:24 by tsurma            #+#    #+#             */
/*   Updated: 2024/05/22 17:38:41 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	allocs(pthread_t **s, t_philo **t, pthread_mutex_t **f, t_house *h)
{

	*s = malloc((h->nmb_philo + 1) * sizeof(pthread_t));
	if (!*s)
		return (ENOMEM);
	*t = malloc((h->nmb_philo + 1) * sizeof(t_philo));
	if (!*t)
	{
		free(*s);
		return (ENOMEM);
	}
	*f = malloc((h->nmb_philo + 1) * sizeof(pthread_mutex_t));
	if (!*f)
	{
		free(*s);
		free(*t);
		return (ENOMEM);
	}
	return (0);
}

static int	assignments(t_philo *tablet, pthread_mutex_t *forks, t_house *house)
{
	int	i;

	i = -1;
	while (++i <= house->nmb_philo)
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (1);
	i = 0;
	while (++i <= house->nmb_philo)
	{
		tablet[i].rules = house;
		tablet[i].nmb_thrd = i;
		tablet[i].print = &forks[0];
		tablet[i].l_fork = &forks[i];
		tablet[i].must_eat = house->tme_must_eat;
		tablet[i].last_meal = 0;
		if (i < house->nmb_philo)
			tablet[i].r_fork = &forks[i + 1];
		else
			tablet[i].r_fork = &forks[1];
	}
	return (0);
}

int	thread_weaver(t_house *house)
{
	int				i;
	pthread_t		*symposium;
	t_philo			*tablet;
	pthread_mutex_t	*forks;

	if (allocs(&symposium, &tablet, &forks, house) == ENOMEM)
		return (ENOMEM);
	if (assignments(tablet, forks, house) != 0)
		return (1);
	i = 0;
	gettimeofday(&house->tv, NULL);
	house->start = house->tv.tv_sec * 1000 + house->tv.tv_usec / 1000;
	while (++i <= house->nmb_philo)
		pthread_create(&symposium[i], NULL, &plato, &tablet[i]);
	i = 0;
	while (++i <= house->nmb_philo)
		pthread_join(symposium[i], NULL);
	i = -1;
	while (++i <= house->nmb_philo)
		pthread_mutex_destroy(&forks[i]);
	free(tablet);
	free(symposium);
	free(forks);
	return (0);
}
