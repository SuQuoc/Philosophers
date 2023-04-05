/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:01:26 by qtran             #+#    #+#             */
/*   Updated: 2023/04/04 19:37:56 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void get_time_in_ms(long long *time_in_ms) //sets the timestamp relative to the start
{
    struct timeval t_of_day;
    gettimeofday(&t_of_day, NULL);
    *time_in_ms = t_of_day.tv_sec * 1000 + t_of_day.tv_usec / 1000;
}

void set_rel_timestamp(t_philo *philo)
{
    philo->timestamp = philo->t_in_ms - philo->data->t_start_in_ms;
}
