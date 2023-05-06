/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:40:01 by qtran             #+#    #+#             */
/*   Updated: 2023/04/26 13:58:15 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*look_if_died(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	usleep((philo->time_to_die) * 1000);
	pthread_mutex_lock(&philo->data->time_print_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	set_rel_timestamp(philo);
	if (philo->data->death_bool == 0 && philo->t_in_ms
		- philo->last_meal >= philo->time_to_die)
	{
		if (philo->data->n_meals > 0 && philo->meals == philo->data->n_meals)
		{
			pthread_mutex_unlock(&philo->data->death_lock);
			pthread_mutex_unlock(&philo->data->time_print_lock);
			return (NULL);
		}
		philo->data->death_bool = 1;
		printf("%u %d died\n", philo->timestamp, philo->name);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_unlock(&philo->data->time_print_lock);
	return (NULL);
}

int	all_alive(t_data *ptr)
{
	if (ptr->death_bool == 1)
		return (0);
	return (1);
}

int	all_alive2(t_data *ptr)
{
	pthread_mutex_lock(&ptr->death_lock);
	if (ptr->death_bool == 1)
	{
		pthread_mutex_unlock(&ptr->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&ptr->death_lock);
	return (1);
}
