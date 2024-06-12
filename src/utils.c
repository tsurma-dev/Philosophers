/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:11:48 by tsurma            #+#    #+#             */
/*   Updated: 2024/06/12 14:49:07 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

	if (i == 1)
		return (-1);
	pthread_mutex_lock(tablet->print);
	time = gtod() - tablet->rules->start;
	if (mes == DIED)
	{
		printf("%lli %i has died\n", time, tablet->nmb_thrd);
		tablet->rules->is_dead = 1;
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

int	ft_atoi(const char *nptr)
{
	int	i;
	int	m;
	int	r;

	i = 0;
	r = 0;
	m = 0;
	while (nptr[i] && (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			m = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = (r * 10) + (nptr[i] - 48);
		i++;
	}
	if (m == 1)
		return (-r);
	return (r);
}

// void	print_struct(t_house *house)
// {
// 	printf("Num of Philo:\t%i\n", house->nmb_philo);
// 	printf("Time to die:\t%i\n", house->tme_die);
// 	printf("Time to eat:\t%i\n", house->tme_eat);
// 	printf("Time to sleep:\t%i\n", house->tme_slp);
// 	printf("Must eat:\t%i\n", house->tme_must_eat);
// }
