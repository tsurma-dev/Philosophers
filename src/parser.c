/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:37:19 by tsurma            #+#    #+#             */
/*   Updated: 2024/06/12 18:18:36 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isdigit(char *str);

int	parser(int argc, char **argv, t_house *house)
{
	int	i;

	if (argc != 4 && argc != 5)
		return (EINVAL);
	argv++;
	i = -1;
	while (++i < argc && ft_isdigit(argv[i]) == 0)
		;
	if (i != argc)
		return (EINVAL);
	i = -1;
	while (argv[++i])
		*((int *)(house) + i) = ft_atoi(argv[i]);
	return (0);
}

static int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		++i;
	if (str[i] == '\0' && i > 0)
		return (0);
	return (1);
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
