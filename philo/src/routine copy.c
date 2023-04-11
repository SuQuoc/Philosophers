/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:18:33 by qtran             #+#    #+#             */
/*   Updated: 2023/04/11 13:21:57 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void philo_thinks(t_philo *philo)
{
    if (all_alive2(philo->data) == 0)
        return;
        
    pthread_mutex_lock(&philo->data->time_print_lock);
    set_rel_timestamp(philo);
    printf("%u %d is thinking\n", philo->timestamp, philo->name);
    pthread_mutex_unlock(&philo->data->time_print_lock);
}



void philo_sleeps(t_philo *philo)
{
    if (all_alive2(philo->data) == 0)
        return;
    //pthread_mutex_lock(&philo->data->time_print_lock);
    //set_rel_timestamp(philo);
    //printf("%u %d is sleeping\n", philo->timestamp, philo->name);
    //pthread_mutex_unlock(&philo->data->time_print_lock);
    protected_print(philo, "is sleeping");
    usleep(philo->data->t_sleep * 1000);
}


void philo_eats(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *sec)
{
    int eating_time;

    if (all_alive2(philo->data) == 0)
        return ;
        
    grab_first_fork_if_w_grab_second(philo, first, sec);
    pthread_mutex_lock(&philo->data->time_print_lock);
    set_rel_timestamp(philo);
    if (all_alive(philo->data))
        printf("%u %d is eating\n", philo->timestamp, philo->name);
    eating_time = philo->data->t_eat;
    pthread_mutex_unlock(&philo->data->time_print_lock);
    usleep(eating_time * 1000);
    give_forks_back(first, sec);
    pthread_mutex_lock(&philo->data->time_print_lock);
    set_rel_timestamp(philo);
    philo->last_meal = philo->t_in_ms;
    philo->meals++;
    pthread_mutex_unlock(&philo->data->time_print_lock);
}

void grab_first_fork_if_w_grab_second(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *sec)
{
    if (all_alive2(philo->data) == 0)
        return ;

    pthread_mutex_lock(first);
    pthread_mutex_lock(sec);
    //print_lock(philo, "has taken fork\n",);
    pthread_mutex_lock(&philo->data->time_print_lock);
    set_rel_timestamp(philo);
    if (all_alive2(philo->data))
    {
        printf("%u %d has taken fork\n", philo->timestamp, philo->name);
        printf("%u %d has taken fork\n", philo->timestamp, philo->name);
    }
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
    pthread_t death_checker;
    
    philo = (t_philo *)ptr;
        
    pthread_create(&death_checker, NULL, &look_if_died, philo);
    while(all_alive(philo->data))
    {    
        if (philo->name % 2 != 0)
        {
            philo_eats(philo, philo->r_fork, philo->l_fork);
            philo_sleeps(philo);
            philo_thinks(philo);
        }
        else
        {
            philo_eats(philo, philo->l_fork, philo->r_fork);
            philo_sleeps(philo);
            philo_thinks(philo);
        }
    }
    //pthread_detach(death_checker);
    pthread_join(death_checker, NULL);
    return (NULL);
}
