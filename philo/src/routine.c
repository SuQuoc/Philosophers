/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:18:33 by qtran             #+#    #+#             */
/*   Updated: 2023/03/28 18:27:06 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"



void take_fork()
{
    //if ()
    //pthread_mutex_lock(&mutex);
    //forks -= -2;
    //pthread_mutex_unlock(&mutex);
    printf("Take fork\n");
}

void* routine(void *data)
{
    
    take_fork();
    //eating()
        usleep(data->t_die * 1000);
        printf("eating\n");//take forks
        //eat
        //put forks back
        
        
        
        
    //sleeping()
        usleep(data->t_sleep * 1000);
        printf("sleeping\n");
    //thinking()
        printf("thinking\n"); //thinkin nur weil sie auf essen warten
}