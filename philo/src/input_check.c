/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:24:59 by qtran             #+#    #+#             */
/*   Updated: 2023/04/12 16:00:10 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

static int	check_if_numeric(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	input_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (j == 0 && av[i][j] == '+')
				j++;
			else if (check_if_numeric(av[i][j]))
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_lonely_philo_main(char **av)
{
	int	n_philos;

	n_philos = ft_atoi(av[1]);
	if (n_philos == 1)
	{
		usleep(ft_atoi(av[2]));
		printf("%d 1 died\n", ft_atoi(av[2]));
		return (1);
	}
	return (0);
}
