/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:18:33 by qtran             #+#    #+#             */
/*   Updated: 2023/04/12 15:49:13 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_if_full_from_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->n_meals > 0 && philo->meals == philo->data->n_meals)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	return (0);
}

static int	eat_sleep_think(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *sec)
{
	philo_eats(philo, first, sec);
	if (check_if_full_from_eating(philo))
		return (1);
	philo_sleeps(philo);
	protected_print(philo, "is thinking");
	return (0);
}

void	*routine(void *ptr)
{
	t_philo		*philo;
	pthread_t	death_checker;

	philo = (t_philo *)ptr;
	pthread_create(&death_checker, NULL, &look_if_died, philo);
	while (all_alive2(philo->data))
	{
		if (philo->name % 2 != 0)
		{
			if (eat_sleep_think(philo, philo->r_fork, philo->l_fork))
			{
				pthread_join(death_checker, NULL);
				return (NULL);
			}
		}
		else
		{
			usleep(1000);
			if (eat_sleep_think(philo, philo->l_fork, philo->r_fork))
			{
				pthread_join(death_checker, NULL);
				return (NULL);
			}
		}
	}
	pthread_join(death_checker, NULL);
	return (NULL);
}
