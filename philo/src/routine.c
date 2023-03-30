/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:18:33 by qtran             #+#    #+#             */
/*   Updated: 2023/03/30 14:17:51 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void take_fork(t_philo *philo)
{
    printf("Philo number %d\n", philo->name);
    printf("This is my right fork: %p\n", &philo->r_fork);
    printf("This is my left fork: %p\n", &philo->l_fork);
    printf("-------------------\n");
    
    
    //if ()
    //pthread_mutex_lock(&mutex);
    //forks -= -2;
    //pthread_mutex_unlock(&mutex);
    //printf("Take fork\n");
}

void *routine(void *philo)
{
    //take_fork(philo);
    //printf("Philo number %d\n", (t_philo *)philo->name);
    return (philo);
    //eating()
//        if (philos.name % 2 == 0)
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