/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:56:03 by qtran             #+#    #+#             */
/*   Updated: 2023/03/30 14:20:50 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <unistd.h>


void init_data(char **av, t_data *data)
{
    data->n_philos = ft_atoi(av[1]);
    data->forks = data->n_philos;
    data->t_die = ft_atoi(av[2]);
    data->t_eat = ft_atoi(av[3]);
    data->t_sleep = ft_atoi(av[4]);
    if (av[5] != NULL)
        data->n_meals = ft_atoi(av[5]);
    else 
        data->n_meals = 0;
    data->th =(pthread_t *)malloc(sizeof(pthread_t) * data->n_philos); //reserving mem for threads
    init_all_mutex(data); //init forks
}


void init_all_mutex(t_data *data)
{
    int i;

    data->mutex = malloc(sizeof(pthread_mutex_t) * data->n_philos); //reserving mem for forks
    i = 0;
    while (i < data->n_philos)
    {
        pthread_mutex_init(&data->mutex[i], NULL);
        i++;
    }
}




void init_philos(t_data *data, t_philo *philos)
{
    int i;
    philos = malloc(sizeof(t_philo) * data->n_philos);
    
    i = 0;
    while (i < data->n_philos)
    {
        philos[i].name = i + 1;
        philos[i].r_fork = data->mutex[i];
        if (i == 0)
            philos[i].l_fork = data->mutex[data->n_philos - 1 - 1];
        else
            philos[i].l_fork = data->mutex[i - 1]; 
        philos[i].t_last_meal = -1;
        philos[i].meals = 0;
        philos[i].data = data;
        i++;
    }
}
























