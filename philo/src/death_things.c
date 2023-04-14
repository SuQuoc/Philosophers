/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:40:01 by qtran             #+#    #+#             */
/*   Updated: 2023/04/14 16:07:26 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//printf("Current time: %lld\n", philo->t_in_ms);
//printf("Last meal time: %lld\n", philo->last_meal);
//printf("Calc time diff: %lld\n", philo->t_in_ms - philo->last_meal);

void	*look_if_died(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (all_alive2(philo->data))
	{
		usleep((philo->time_to_die) * 1000);
		if (check_if_full_from_eating(philo))
			return (NULL);
		pthread_mutex_lock(&philo->data->time_print_lock);
		pthread_mutex_lock(&philo->data->death_lock);
		set_rel_timestamp(philo);
		if (philo->data->death_bool == 0 && philo->t_in_ms
			- philo->last_meal >= philo->time_to_die)
		{
			philo->data->death_bool = 1;
			printf("%u %d died\n", philo->timestamp, philo->name);
		}
		pthread_mutex_unlock(&philo->data->death_lock);
		pthread_mutex_unlock(&philo->data->time_print_lock);
	}
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
