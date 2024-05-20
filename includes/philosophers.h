/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:18:44 by tsurma            #+#    #+#             */
/*   Updated: 2024/05/20 18:56:52 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>


typedef struct s_philosophers
{
	int	nmb_philo;
	int	tme_die;
	int	tme_eat;
	int	tme_slp;
	int	tme_must_eat;

	int	nmb_thrd;
}	t_philo;
//don't change order;

int		thread_weaver(t_philo *philo);
void	*plato(void *phil);
int		parser(int argc, char **argv, t_philo *philo);
void	print_struct(t_philo *philo);
void	exit_clean(int err);
