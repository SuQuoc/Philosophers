/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_and_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:15:34 by qtran             #+#    #+#             */
/*   Updated: 2023/04/05 14:11:11 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../philo.h"

void destroy_all_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n_philos)
    {
        pthread_mutex_destroy(data->fork[i]);
        free(data->fork[i]);
        i++;
    }
    free(data->fork);
}


void create_threads(t_data *data, t_philo *philos)
{
    char *err;
    int i;

    err = "Error, failed to create thread\n";
    i = 0;
    while(i < data->n_philos)
    {
        init_one_pinoy_boy(data, philos, i);
        i++;
    }
    
    i = 0;
    while (i < data->n_philos)
    {   
        //printf("Philo number %d\n", philos[i].name);
        //printf("Philo number %d\n", philos[i].name);
        if (pthread_create(&data->th[i], NULL, &routine, &philos[i]) != 0)
            write(2, err, ft_strlen(err));
        i++;
        //printf("Thread %d has started\n", i);
    }
    //free(philos);
}


void join_threads(t_data *data)
{
    //printf("\n--------Joining threads-----------\n");
    char *err;
    int i;

    err = "Error, failed to join thread\n";
    i = 0;
    while (i < data->n_philos)
    {
        if (pthread_join(data->th[i], NULL) != 0)
            write(2, err, ft_strlen(err));
        i++;
        //printf("Thread %d has finished execution\n", i);
    }
}