/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:58:09 by qtran             #+#    #+#             */
/*   Updated: 2023/03/30 14:17:43 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

void destroy_all_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i++ < data->n_philos)
        pthread_mutex_destroy(&data->mutex[i]);
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
        printf("Philo number %d\n", philos->name);
        if (pthread_create(&data->th[i], NULL, &routine, &philos[i]) != 0)
            write(2, err, ft_strlen(err));
        i++;
        printf("Thread %d has started\n", i);
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
        printf("Thread %d has finished execution\n", i);
    }
}



int main(int ac, char **av)
{
    //pthread_t th[ft_atoi(av[1])];
    //int forks;
    t_data data;
    t_philo *philos = NULL;
    if (ac < 5 || ac > 6 || input_check(av) == 1)
        return (0);
    printf("Now fun starts\n");
    init_data(av, &data);
    
    init_philos(&data, philos);
    create_threads(&data, philos);
    

    
    
    join_threads(&data);
    destroy_all_mutex(&data);
    free(data.th);
    return (0);
}
