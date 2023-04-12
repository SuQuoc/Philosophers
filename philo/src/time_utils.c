/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:01:26 by qtran             #+#    #+#             */
/*   Updated: 2023/04/12 14:50:21 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	get_time_in_ms(long long *time_in_ms)
{
	struct timeval	t_of_day;

	gettimeofday(&t_of_day, NULL);
	*time_in_ms = t_of_day.tv_sec * 1000 + t_of_day.tv_usec / 1000;
}

void	set_rel_timestamp(t_philo *philo)
{
	if (philo == NULL || philo->data == NULL)
		return ;
	get_time_in_ms(&philo->t_in_ms);
	philo->timestamp = philo->t_in_ms - philo->t_start_in_ms;
}
