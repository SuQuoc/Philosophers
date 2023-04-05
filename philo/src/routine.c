/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:18:33 by qtran             #+#    #+#             */
/*   Updated: 2023/04/05 14:29:18 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void take_fork_test(t_philo *philo) //first routine tests
{
    //printf("Philo number %d\n", philo->name);
    //printf("Philo number %d right fork: %p\n", philo->name, philo->r_fork);
    //printf("Philo number %d left fork: %p\n", philo->name, philo->l_fork);
    //printf("Philo number %d right fork: %d\n", philo->name, philo->rr_fork);
    //printf("Philo number %d left fork: %d\n", philo->name, philo->ll_fork);
    printf("-------------------\n");
    
    
    if (philo->name % 2 != 0)
    {
        if (pthread_mutex_lock(philo->r_fork) == 0)
        {
            printf("Philo number %d grabed right fork: %p\n", philo->name, philo->r_fork);
            if (pthread_mutex_lock(philo->l_fork) == 0)
            {
                printf("Philo number %d grabed left fork after grabbing right: %p\n", philo->name, philo->l_fork);
                printf("-------------------\n");
                if (pthread_mutex_unlock(philo->l_fork) == 0)
                    printf("Philo number %d gave back left fork\n", philo->name);
            }
            if (pthread_mutex_unlock(philo->r_fork) == 0)
                printf("Philo number %d gave back right fork\n", philo->name);
        }   
    }
    else
    {
        if (pthread_mutex_lock(philo->l_fork) == 0)
        {
            printf("Philo number %d grabed left fork: %p\n", philo->name, philo->l_fork);
            if (pthread_mutex_lock(philo->r_fork) == 0)
            {
                printf("Philo number %d grabed right fork after grabbing left: %p\n", philo->name, philo->r_fork);
                printf("-------------------\n");
                if (pthread_mutex_unlock(philo->r_fork) == 0)
                    printf("Philo number %d gave back right fork\n", philo->name);
            }
            if (pthread_mutex_unlock(philo->l_fork) == 0)
                printf("Philo number %d gave back left fork\n", philo->name);
        }       
    }
    
}


void philo_eats(t_philo *philo)
{
    int eating_time;
    pthread_mutex_lock(philo->data->death_lock);//LOCK
    get_time_in_ms(&philo->t_in_ms);
    set_rel_timestamp(philo);
    printf("%lld Philosopher %d is eating\n", philo->timestamp, philo->name);
    eating_time = philo->data->t_eat;
    pthread_mutex_unlock(philo->data->death_lock);//UNLOCK
    
    
    usleep(eating_time * 1000);
    
    pthread_mutex_lock(philo->data->death_lock);//LOCK
    get_time_in_ms(&philo->t_in_ms);
    set_rel_timestamp(philo);
    philo->last_meal = philo->timestamp;
    philo->meals++;
    pthread_mutex_unlock(philo->data->death_lock);//UNLOCK

}

void grab_first_fork_if_w_grab_second(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *sec)
{
    pthread_mutex_lock(first); //LOCK
    get_time_in_ms(&philo->t_in_ms);
    set_rel_timestamp(philo);
    printf("%lld Philo number %d grabed first fork\n", philo->timestamp, philo->name);      
    //printf("%lld Philo number %d grabed first fork: %p\n", philo->timestamp, philo->name, first);
    pthread_mutex_lock(sec); //LOCK

    get_time_in_ms(&philo->t_in_ms);
    set_rel_timestamp(philo);
    printf("%lld Philo number %d grabed sec fork\n", philo->timestamp, philo->name);      
    //printf("%lld Philo number %d grabed sec fork: %p\n", philo->timestamp, philo->name, sec);
    philo_eats(philo);
    
    pthread_mutex_unlock(sec);//UNLOCK   
    pthread_mutex_unlock(first);//UNLOCK
    
    //if (pthread_mutex_lock(first) == 0) //LOCK
    //{
    //    get_time_in_ms(&philo->t_in_ms);
    //    set_rel_timestamp(philo);
    //    printf("%lld Philo number %d grabed first fork\n", philo->timestamp, philo->name);      
    //    //printf("%lld Philo number %d grabed first fork: %p\n", philo->timestamp, philo->name, first);
    //    if (pthread_mutex_lock(sec) == 0)
    //    {
    //        get_time_in_ms(&philo->t_in_ms);
    //        set_rel_timestamp(philo);
    //        printf("%lld Philo number %d grabed sec fork\n", philo->timestamp, philo->name);      
    //        //printf("%lld Philo number %d grabed sec fork: %p\n", philo->timestamp, philo->name, sec);
    //        philo_eats(philo);
    //        pthread_mutex_unlock(sec);
    //    }
    //    pthread_mutex_unlock(first);
    //}
}



void philo_sleeps(t_philo *philo)
{
    
    pthread_mutex_lock(philo->data->death_lock); //LOCK
    
    printf("%lld Philo number %d is sleeping\n", philo->timestamp, philo->name);
    pthread_mutex_unlock(philo->data->death_lock); //UNLOCK
    
    usleep(philo->data->t_sleep * 1000);
}


void philo_thinks(t_philo *philo)
{
    pthread_mutex_lock(philo->data->death_lock); //LOCK
    
    get_time_in_ms(&philo->t_in_ms);
    set_rel_timestamp(philo);
    printf("%lld Philo number %d is thinking\n", philo->timestamp, philo->name);

    pthread_mutex_unlock(philo->data->death_lock); //UNLOCK
}

void *routine(void *ptr)
{
    t_philo *philo;
    
    philo = (t_philo *)ptr;

   
    while(all_alive(philo->data) == 0)
    {    
        //check_death(philo); 
        if (philo->name % 2 != 0)
        {
            grab_first_fork_if_w_grab_second(philo, philo->r_fork, philo->l_fork);
            //if (grab_first_fork_if_w_grab_second(philo, philo->r_fork, philo->l_fork) == 1);
            philo_sleeps(philo);
            philo_thinks(philo);
        }
        else
        {
            grab_first_fork_if_w_grab_second(philo, philo->l_fork, philo->r_fork);
            philo_sleeps(philo);
            philo_thinks(philo);
        }
    }
    //free(philo);
    return (NULL);
}






void take_fork(t_philo *philo) //überflüssig jz --> routine
{
    if (philo->name % 2 != 0)
    {
        grab_first_fork_if_w_grab_second(philo, philo->r_fork, philo->l_fork);
        //if (grab_first_fork_if_w_grab_second(philo, philo->r_fork, philo->l_fork) == 1);
            //philo_sleeps(philo);
            //philo_thinks(philo);
    }

    else
    {
        grab_first_fork_if_w_grab_second(philo, philo->l_fork, philo->r_fork);
    }
}


    //    printf("Take fork\n");
    //
    //pthread_mutex_unlock(&mutex);