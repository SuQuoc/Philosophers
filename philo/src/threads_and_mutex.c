/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_and_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:15:34 by qtran             #+#    #+#             */
/*   Updated: 2023/04/11 17:42:17 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../philo.h"

void destroy_all_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    //pthread_mutex_lock(&data->death_lock);//
    //pthread_mutex_unlock(&data->death_lock);//

    pthread_mutex_destroy(&data->death_lock);
    pthread_mutex_destroy(&data->time_print_lock);
}


void create_threads(t_data *data, t_philo *philos)
{
    char *err;
    int i;

    err = "Error, failed to create thread\n";
    i = 0;
    get_time_in_ms(&data->t_start_in_ms);
    //printf("Start time in ms FROM MAIN: %lld\n", data->t_start_in_ms);
    while(i < data->n_philos)
    {
        init_one_pinoy_boy(data, philos, i);
        i++;
    }
    
    i = 0;
    while (i < data->n_philos)
    {   
        if (pthread_create(&data->th[i], NULL, &routine, &philos[i]) != 0)
            write(2, err, ft_strlen(err));
        i++;
    }
}


void join_threads(t_data *data)
{
    char *err;
    int i;

    err = "Error, failed to join thread\n";
    i = 0;
    while (i < data->n_philos)
    {
        if (pthread_join(data->th[i], NULL) != 0)
            write(2, err, ft_strlen(err));
        i++;
    }
}