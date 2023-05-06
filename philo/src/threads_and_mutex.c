/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_and_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:15:34 by qtran             #+#    #+#             */
/*   Updated: 2023/04/27 10:58:05 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	destroy_all_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			return (1);
		i++;
	}
	pthread_mutex_lock(&data->time_print_lock);
	pthread_mutex_unlock(&data->time_print_lock);
	if (pthread_mutex_destroy(&data->death_lock) != 0)
		return (1);
	if (pthread_mutex_destroy(&data->time_print_lock) != 0)
		return (1);
	return (0);
}

int	create_threads(t_data *data, t_philo *philos)
{
	get_time_in_ms(&data->t_start_in_ms);
	if (create_odd_threads(data, philos) != 0)
		return (1);
	usleep(1000);
	if (create_even_threads(data, philos) != 0)
		return (1);
	return (0);
}

int	join_n_threads(t_data *data, int n)
{
	int		i;
	char	*err;

	err = "Error, failed to join thread\n";
	i = 0;
	while (i < n)
	{
		if (pthread_join(data->th[i], NULL) != 0)
		{
			write(2, err, ft_strlen(err));
			return (1);
		}
		i++;
	}
	return (0);
}
