/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:48:37 by qtran             #+#    #+#             */
/*   Updated: 2023/04/12 16:02:28 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_sleeps(t_philo *philo)
{
	protected_print(philo, "is sleeping");
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
	usleep(eating_time * 1000);
	pthread_mutex_lock(&philo->data->death_lock);
	philo->meals++;
	pthread_mutex_unlock(&philo->data->death_lock);
	give_forks_back(first, sec);
}

void	grab_first_fork_if_w_grab_second(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *sec)
{
	pthread_mutex_lock(first);
	pthread_mutex_lock(sec);
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
	return ;
}
