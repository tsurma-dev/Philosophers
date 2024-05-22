/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:18:44 by tsurma            #+#    #+#             */
/*   Updated: 2024/05/22 18:01:17 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <errno.h>
# include <sys/time.h>

typedef enum messages
{
	DIED,
	FORK,
	EAT,
	SLEEP,
	THINK
}	t_message;

typedef struct s_houserules
{
	int				nmb_philo;
	int				tme_die;
	int				tme_eat;
	int				tme_slp;
	int				tme_must_eat;
	long long		start;
	struct timeval	tv;
}	t_house;
//don't change order;

typedef struct s_philosopher
{
	struct timeval	priv;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print;

	t_house			*rules;
	int				must_eat;
	int				nmb_thrd;
	long long		last_meal;
}	t_philo;


int		thread_weaver(t_house *house);
void	*plato(void *house);
int		parser(int argc, char **argv, t_house *house);
void	print_struct(t_house *house);
void	*print_message(int mes, t_philo *tablet);
int		eating(t_philo *tablet);

#endif
