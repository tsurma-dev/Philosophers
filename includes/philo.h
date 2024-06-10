/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:18:44 by tsurma            #+#    #+#             */
/*   Updated: 2024/06/10 15:48:59 by tsurma           ###   ########.fr       */
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
	pthread_mutex_t	*sip_all;
	long long		start;
	int				is_dead;
}	t_house;
//don't change order;

typedef struct s_philosopher
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*sip;

	t_house			*rules;
	long long		last_meal;
	int				must_eat;
	int				nmb_thrd;
	int				is_dead;
}	t_philo;

long long	gtod(void);
int			thread_weaver(t_house *house);
void		*socrates(void *house);
int			parser(int argc, char **argv, t_house *house);
int			print_message(int mes, t_philo *tablet);
int			eating(t_philo *tablet);
void		*hemlock(void *tab);
int			ft_atoi(const char *nptr);
int			check_dead(t_philo *tab);
void		set_dead(t_philo *tab, int j);
int			check_dead_all(t_philo *tab);
void		set_dead_all(t_philo *tab, int j);


#endif
