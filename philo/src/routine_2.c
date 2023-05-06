/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:48:37 by qtran             #+#    #+#             */
/*   Updated: 2023/04/26 13:36:44 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_sleeps(t_philo *philo)
{
	protected_print(philo, "is sleeping");
	if (all_alive2(philo->data))
		usleep(philo->data->t_sleep * 1000);
}

void	philo_eats(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *sec)
{
	int	eating_time;

	grab_first_fork_if_w_grab_second(philo, first, sec);
	protected_print(philo, "is eating");
	pthread_mutex_lock(&philo->data->time_print_lock);
	set_rel_timestamp(philo);
	philo->last_meal = philo->t_in_ms;
	eating_time = philo->data->t_eat;
	pthread_mutex_unlock(&philo->data->time_print_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->death_bool == 0)
	{
		philo->meals++;
		pthread_mutex_unlock(&philo->data->death_lock);
		usleep(eating_time * 1000);
	}
	else
		pthread_mutex_unlock(&philo->data->death_lock);
	give_forks_back(first, sec);
}

void	grab_first_fork_if_w_grab_second(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *sec)
{
	pthread_mutex_lock(sec);
	pthread_mutex_lock(first);
	if (all_alive2(philo->data))
	{
		pthread_mutex_lock(&philo->data->time_print_lock);
		set_rel_timestamp(philo);
		printf("%u %d has taken fork\n", philo->timestamp, philo->name);
		set_rel_timestamp(philo);
		printf("%u %d has taken fork\n", philo->timestamp, philo->name);
		pthread_mutex_unlock(&philo->data->time_print_lock);
	}
}

void	give_forks_back(pthread_mutex_t *first, pthread_mutex_t *sec)
{
	pthread_mutex_unlock(sec);
	pthread_mutex_unlock(first);
}

void	protected_print(t_philo *philo, char *msg)
{
	if (all_alive2(philo->data))
	{
		pthread_mutex_lock(&philo->data->time_print_lock);
		set_rel_timestamp(philo);
		printf("%u %d %s\n", philo->timestamp, philo->name, msg);
		pthread_mutex_unlock(&philo->data->time_print_lock);
	}
}
