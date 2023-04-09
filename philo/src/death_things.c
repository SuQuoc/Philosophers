/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:40:01 by qtran             #+#    #+#             */
/*   Updated: 2023/04/09 18:01:10 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *look_if_died(void *ptr)
{
    t_philo *philo;
    philo = (t_philo *)ptr;
    
    while (all_alive2(philo->data))
    {
        usleep((philo->time_to_die) * 1000);
        pthread_mutex_lock(&philo->data->time_print_lock); //LOCK
        set_rel_timestamp(philo);
        pthread_mutex_lock(&philo->data->death_lock); //LOCK
        //printf("Current time: %lld\n", philo->t_in_ms);
        //printf("Last meal time: %lld\n", philo->last_meal);
        //printf("Calc time diff: %lld\n", philo->t_in_ms - philo->last_meal);
        if (philo->data->death_bool == 0 && (philo->t_in_ms - philo->last_meal) >= philo->time_to_die)
        {
            //else raus nehmen noch
            philo->data->death_bool = 1;
            pthread_mutex_unlock(&philo->data->death_lock); //UNLOCK
            printf("%u %d died\n", philo->timestamp, philo->name);
            pthread_mutex_unlock(&philo->data->time_print_lock); //UNLOCK
        }
        else
        {
            pthread_mutex_unlock(&philo->data->time_print_lock); //UNLOCK
            pthread_mutex_unlock(&philo->data->death_lock); //UNLOCK
        }
    }
    return NULL;
}

void check_death(t_philo *philo)
{
    pthread_t death_checker;

    pthread_create(&death_checker, NULL, &look_if_died, philo);
    pthread_detach(death_checker);
}

int all_alive(t_data *ptr)
{
    //pthread_mutex_lock(&ptr->death_lock);
    if (ptr->death_bool == 1)
    {
      //  pthread_mutex_unlock(&ptr->death_lock);
        return (0);
    }
    //pthread_mutex_unlock(&ptr->death_lock);
    return (1);
}


int all_alive2(t_data *ptr)
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
