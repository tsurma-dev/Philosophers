/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:52:47 by tsurma            #+#    #+#             */
/*   Updated: 2024/05/20 19:23:09 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	static t_philo	philo;

	argc--;
	if (parser(argc, argv, &philo) != 0)
		exit_clean(EINVAL);

	thread_weaver(&philo);
	// print_struct(&philo);

	return (0);
}

int	thread_weaver(t_philo *philo)
{
	int			i;
	pthread_t	*symposium;

	symposium = malloc((philo->nmb_philo + 1) * sizeof(pthread_t));
	i = 0;
	while (++i <= philo->nmb_philo)
	{
		philo->nmb_thrd = i;
		pthread_create(&symposium[i], NULL, &plato, philo);
	}
	i = 0;
	while (++i <= philo->nmb_philo)
		pthread_join(symposium[i], NULL);
	free(symposium);
	return (0);
}

void	*plato(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	printf("This is thread: %i\n", philo->nmb_thrd);
	return (NULL);
}


void	print_struct(t_philo *philo)
{
	printf("Num of Philo:\t%i\n", philo->nmb_philo);
	printf("Time to die:\t%i\n", philo->tme_die);
	printf("Time to eat:\t%i\n", philo->tme_eat);
	printf("Time to sleep:\t%i\n", philo->tme_slp);
	printf("Must eat:\t%i\n", philo->tme_must_eat);
}

void	exit_clean(int err)
{
	perror("Invalid arguments");
	exit(err);
}


