/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:18:33 by qtran             #+#    #+#             */
/*   Updated: 2023/04/07 18:02:21 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void philo_thinks(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->death_lock); //LOCK
    if (philo->data->death_bool == 1)
    {
        pthread_mutex_unlock(&philo->data->death_lock); //LOCK
        return;
    }
    pthread_mutex_unlock(&philo->data->death_lock); //LOCK

        
    pthread_mutex_lock(&philo->data->time_print_lock); //LOCK
    set_rel_timestamp(philo);
    printf("%u %d is thinking\n", philo->timestamp, philo->name);
    pthread_mutex_unlock(&philo->data->time_print_lock); //UNLOCK
}



void philo_sleeps(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->death_lock); //LOCK
    if (philo->data->death_bool == 1)
    {
        pthread_mutex_unlock(&philo->data->death_lock); //UNLOCK
        return;
    }
    pthread_mutex_unlock(&philo->data->death_lock); //UNLOCK

    pthread_mutex_lock(&philo->data->time_print_lock); //LOCK
    set_rel_timestamp(philo);
   // if (philo->data->death_bool == 0)
    printf("%u %d is sleeping\n", philo->timestamp, philo->name);
    pthread_mutex_unlock(&philo->data->time_print_lock); //UNLOCK
    
    usleep(philo->data->t_sleep * 1000);
}


void philo_eats(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *sec)
{
    int eating_time;

    pthread_mutex_lock(&philo->data->death_lock); //LOCK
    if (philo->data->death_bool == 1)
    {
        pthread_mutex_unlock(&philo->data->death_lock); //UNLOCK
        return;
    }
    pthread_mutex_unlock(&philo->data->death_lock); //UNLOCK


    grab_first_fork_if_w_grab_second(philo, first, sec);
    
    pthread_mutex_lock(&philo->data->time_print_lock);//LOCK
    set_rel_timestamp(philo);   
    printf("%u %d is eating\n", philo->timestamp, philo->name);
    eating_time = philo->data->t_eat;
    pthread_mutex_unlock(&philo->data->time_print_lock);//UNLOCK

    usleep(eating_time * 1000);
    give_forks_back(first, sec);
        
    pthread_mutex_lock(&philo->data->time_print_lock);//LOCK
    set_rel_timestamp(philo);
    philo->last_meal = philo->timestamp;
    philo->meals++;
    pthread_mutex_unlock(&philo->data->time_print_lock);//UNLOCK
}

void grab_first_fork_if_w_grab_second(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *sec)
{
    pthread_mutex_lock(first);
    pthread_mutex_lock(&philo->data->time_print_lock);
    set_rel_timestamp(philo);
    printf("%u %d has taken fork\n", philo->timestamp, philo->name);//first fork      
    pthread_mutex_unlock(&philo->data->time_print_lock);
    
    
    pthread_mutex_lock(sec);
    pthread_mutex_lock(&philo->data->time_print_lock);
    set_rel_timestamp(philo);
    printf("%u %d has taken fork\n", philo->timestamp, philo->name);//sec      
    pthread_mutex_unlock(&philo->data->time_print_lock);
}

void give_forks_back(pthread_mutex_t *first, pthread_mutex_t *sec)
{
    pthread_mutex_unlock(sec);
    pthread_mutex_unlock(first);
}

void *routine(void *ptr)
{
    t_philo *philo;
    
    philo = (t_philo *)ptr;

    int i = 0;
    //while(i < 10)
    
    while(all_alive(philo->data))
    {    
        if (philo->name % 2 != 0)
        {
            check_death(philo);
            philo_eats(philo, philo->r_fork, philo->l_fork);
            check_death(philo);
            philo_sleeps(philo);
            philo_thinks(philo);

        }
        else
        {
            check_death(philo);
            philo_eats(philo, philo->l_fork, philo->r_fork);
            check_death(philo);
            philo_sleeps(philo);
            philo_thinks(philo);
        }
        i++;
    }
    return (NULL);
}
