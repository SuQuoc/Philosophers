/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:18:33 by qtran             #+#    #+#             */
/*   Updated: 2023/04/17 14:52:25 by qtran            ###   ########.fr       */
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
	usleep(500);
	return (0);
}

// void	*routine(void *ptr)
// {
	// t_philo		*philo;
	// pthread_t	death_checker;
// 
	// philo = (t_philo *)ptr;
	// while (all_alive2(philo->data))
	// {
		// pthread_create(&death_checker, NULL, &look_if_died, philo);
		// if (philo->name % 2 != 0)
		// {
			// if (eat_sleep_think(philo, philo->r_fork, philo->l_fork))
				// return (pthread_detach(death_checker), NULL);
		// }
		// else
		// {
			//usleep(1000);
			// if (eat_sleep_think(philo, philo->l_fork, philo->r_fork))
				// return (pthread_detach(death_checker), NULL);
		// }
		// pthread_detach(death_checker);
	// }
	// return (NULL);
// }

void	*routine(void *ptr)
{
	t_philo		*philo;
	pthread_t	death_checker;

	philo = (t_philo *)ptr;
	while (all_alive2(philo->data))
	{
		pthread_create(&death_checker, NULL, &look_if_died, philo);
		if (philo->name % 2 != 0)
			eat_sleep_think(philo, philo->r_fork, philo->l_fork);
		else
			eat_sleep_think(philo, philo->l_fork, philo->r_fork);
		pthread_detach(death_checker);
		if (check_if_full_from_eating(philo) == 1)
			break ;
	}
	usleep((philo->time_to_die) * 1000);
	return (NULL);
}
//müsste nur t_die - eat abwarten 
//-->main thread terminates before dath_checker and
//thread therefore is not properly cleanud up
