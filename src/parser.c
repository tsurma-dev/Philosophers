/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:37:19 by tsurma            #+#    #+#             */
/*   Updated: 2024/05/22 15:18:46 by tsurma           ###   ########.fr       */
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
		*((int *)(house) + i) = atoi(argv[i]);
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
