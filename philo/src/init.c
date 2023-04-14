/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:56:03 by qtran             #+#    #+#             */
/*   Updated: 2023/04/14 15:19:37 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <unistd.h>

void	init_data(char **av, t_data *data)
{
	data->n_philos = ft_atoi(av[1]);
	data->t_start_in_ms = -1;
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->death_bool = 0;
	if (av[5] != NULL)
		data->n_meals = ft_atoi(av[5]);
	else
		data->n_meals = 0;
	data->th = (pthread_t *)malloc(sizeof(pthread_t) * data->n_philos);
	init_all_fork_mutex(data);
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->time_print_lock, NULL);
}

void	init_all_fork_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	init_one_pinoy_boy(t_data *data, t_philo *philos, int i)
{
	philos[i].name = i + 1;
	philos[i].r_fork = &data->forks[i];
	if (i == 0)
		philos[i].l_fork = &data->forks[data->n_philos - 1];
	else
		philos[i].l_fork = &data->forks[i - 1];
	philos[i].meals = 0;
	philos[i].time_to_die = data->t_die;
	philos[i].t_in_ms = -1;
	philos[i].last_meal = data->t_start_in_ms;
	philos[i].t_start_in_ms = data->t_start_in_ms;
	philos[i].timestamp = 0;
	philos[i].data = data;
}
