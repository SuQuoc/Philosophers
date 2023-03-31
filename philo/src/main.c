/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:58:09 by qtran             #+#    #+#             */
/*   Updated: 2023/03/31 19:00:50 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

void destroy_all_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n_philos)
    {
        pthread_mutex_destroy(data->mutex[i]);
        free(data->mutex[i]);
        i++;
    }
    free(data->mutex);
}


void create_threads(t_data *data, t_philo *philos)
{
    char *err;
    int i;

    err = "Error, failed to create thread\n";
    i = 0;
   
    while (i < data->n_philos)
    {   
        init_one_pinoy_boy(data, philos, i);
        //printf("Philo number %d\n", philos[i].name);
        if (pthread_create(&data->th[i], NULL, &routine, &philos[i]) != 0)
            write(2, err, ft_strlen(err));
        i++;
        printf("Thread %d has started\n", i);
    }
    //free(philos);
}


void join_threads(t_data *data)
{
    printf("\n--------Joining threads-----------\n");
    char *err;
    int i;

    err = "Error, failed to join thread\n";
    i = 0;
    while (i < data->n_philos)
    {
        if (pthread_join(data->th[i], NULL) != 0)
            write(2, err, ft_strlen(err));
        i++;
        printf("Thread %d has finished execution\n", i);
    }
}



int main(int ac, char **av)
{
    t_data data;
    t_philo *philos;
    if (ac < 5 || ac > 6 || input_check(av) == 1)
        return (0);
    printf("Now fun starts\n");
    init_data(av, &data);
    
    philos = malloc(sizeof(t_philo) * data.n_philos);
    set_start_timestamp_in_ms(&data);
    create_threads(&data, philos); //inits all philos and the threads 
    //sleep(2); //ohne den sleep kommen errors weil free(to fast ist)
    
    join_threads(&data);
    free(philos);
    destroy_all_mutex(&data);
    free(data.th);
    return (0);
}
