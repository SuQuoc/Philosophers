/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:58:09 by qtran             #+#    #+#             */
/*   Updated: 2023/04/12 15:59:09 by qtran            ###   ########.fr       */
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
	create_threads(&data, philos);
	join_threads(&data);
	destroy_all_mutex(&data);
	free(philos);
	free(data.th);
	free(data.forks);
	return (0);
}
