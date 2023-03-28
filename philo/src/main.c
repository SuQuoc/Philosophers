/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:58:09 by qtran             #+#    #+#             */
/*   Updated: 2023/03/28 18:35:04 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>


void init_all_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i++ < data->n_philos)
        pthread_mutex_init(&data->mutex[i], NULL);
}


void destroy_all_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i++ < data->n_philos)
        pthread_mutex_init(&data->mutex[i], NULL);
}

int main(int ac, char **av)
{
    //pthread_t th[ft_atoi(av[1])];
    //int forks;
    t_data data;
    if (ac < 5 || ac > 6 || input_check(av) == 1)
        return (0);
    printf("Now fun starts\n");
    init_data(&data);
    init_all_mutex(&data);
    create_threads(&data);
    

    
    
    join_threads(&data);


    destroy_all_mutex(&data);
    return (0);
}
