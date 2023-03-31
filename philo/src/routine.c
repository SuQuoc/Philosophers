/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:18:33 by qtran             #+#    #+#             */
/*   Updated: 2023/03/31 19:03:00 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void take_fork_test(t_philo *philo)
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


void set_timestamp_in_ms(t_philo *ptr) //sets the timestamp relative to the start
{
    gettimeofday(&ptr->get_t_of_day, NULL);
    ptr->timestamp_in_ms = ptr->get_t_of_day.tv_sec * 1000 + ptr->get_t_of_day.tv_usec / 1000 - ptr->data->t_start; 
}

void set_start_timestamp_in_ms(t_data *ptr)
{
    gettimeofday(&ptr->get_t_of_day, NULL);
    ptr->t_start = ptr->get_t_of_day.tv_sec * 1000 + ptr->get_t_of_day.tv_usec / 1000; 
}


void eats(t_philo *philo)
{
    
}

void grab_first_fork_if_w_grab_second(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *sec)
{
    if (pthread_mutex_lock(first) == 0)
    {
        set_timestamp_in_ms(philo);
        printf("%lld Philo number %d grabed first fork: %p\n", philo->timestamp_in_ms, philo->name, first);
        if (pthread_mutex_lock(sec) == 0)
        {
            printf("%lld Philo number %d grabed sec fork: %p\n", philo->timestamp_in_ms, philo->name, sec);
            printf("-------------------\n");
            printf("%lld Philo number %d grabed sec fork: %p\n", philo->timestamp_in_ms, philo->name, sec);
            if (pthread_mutex_unlock(sec) == 0)
                printf("Philo number %d gave back sec fork: %p\n", philo->name, sec);
        }
        if (pthread_mutex_unlock(first) == 0)
            printf("Philo number %d gave back first fork: %p\n", philo->name, first);
    }
}



void take_fork(t_philo *philo)
{
    if (philo->name % 2 != 0)
    {
        grab_first_fork_if_w_grab_second(philo, philo->r_fork, philo->l_fork);
    }

    else
    {
        grab_first_fork_if_w_grab_second(philo, philo->l_fork, philo->r_fork);
    }
}


    //    printf("Take fork\n");
    //
    //pthread_mutex_unlock(&mutex);


void *routine(void *philo)
{
    take_fork(philo);
    //printf("Philo number %d\n", (t_philo *)philo->name);
    return (philo);
    //eating()
//        
//            l_fork;
//        else
//            r_fork;
//        usleep(data->t_die * 1000);
//        printf("eating\n");//take forks
//        //eat
//        //put forks back
//        
//        
//        
//        
//    //sleeping()
//        usleep(data->t_sleep * 1000);
//        printf("sleeping\n");
//    //thinking()
//        printf("thinking\n"); //thinkin nur weil sie auf essen warten
}