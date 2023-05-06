/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:58:09 by qtran             #+#    #+#             */
/*   Updated: 2023/04/26 15:26:21 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (ac < 5 || ac > 6 || input_check(av) == 1)
	{
		printf("Error input incorrect!\n");
		return (0);
	}
	if (check_lonely_philo_main(av))
		return (0);
	init_data(av, &data);
	philos = malloc(sizeof(t_philo) * data.n_philos);
	if (philos == NULL || create_threads(&data, philos) != 0)
		return (free_everything(&data, philos), 1);
	if (join_n_threads(&data, data.n_philos) != 0
		|| destroy_all_mutex(&data) != 0)
		return (free_everything(&data, philos), 1);
	return (free_everything(&data, philos), 0);
}

void	free_everything(t_data *data, t_philo *philos)
{
	if (data->th != NULL)
	{
		free(data->th);
		data->th = NULL;
	}
	if (data->forks != NULL)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (philos != NULL)
	{
		free(philos);
		philos = NULL;
	}
}
