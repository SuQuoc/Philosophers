/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:56:03 by qtran             #+#    #+#             */
/*   Updated: 2023/04/05 14:08:55 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <unistd.h>


void init_data(char **av, t_data *data)
{
    data->n_philos = ft_atoi(av[1]);
    data->forks = data->n_philos;
    get_time_in_ms(&data->t_start_in_ms);
    data->t_die = ft_atoi(av[2]);
    data->t_eat = ft_atoi(av[3]);
    data->t_sleep = ft_atoi(av[4]);
    if (av[5] != NULL)
        data->n_meals = ft_atoi(av[5]);
    else 
        data->n_meals = 0;
    data->th =(pthread_t *)malloc(sizeof(pthread_t) * data->n_philos); //reserving mem for threads
    init_all_fork_mutex(data); //init forks
    data->death_bool = 0; 
    pthread_mutex_init(data->death_lock, NULL);
    //pthread_mutex_init(&death, NULL);
}


void init_all_fork_mutex(t_data *data)
{
    int i;

    data->fork = malloc(sizeof(pthread_mutex_t *) * data->n_philos); //reserving mem for forks
    i = 0;
    while (i < data->n_philos)
    {
        data->fork[i] = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(data->fork[i], NULL);
        i++;
    }
}


void init_one_pinoy_boy(t_data *data, t_philo *philos, int i)
{
    philos[i].name = i + 1;
    philos[i].r_fork = data->fork[i];
    philos[i].rr_fork = i;
    if (i == 0)
    {
        philos[i].l_fork = data->fork[data->n_philos - 1];
        philos[i].ll_fork = data->n_philos - 1;
    }
    else
    {
        philos[i].l_fork = data->fork[i - 1]; 
        philos[i].ll_fork = i - 1; 
    }
    
    //shared either with main or death check thread
    philos[i].meals = 0;
    philos[i].last_meal = data->t_start_in_ms;
    philos[i].data = data;
    philos[i].t_in_ms = -1;
    philos[i].timestamp = 0;
    philos[i].time_to_die = data->t_die;
}




/*
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
        {
            philos[i].l_fork = data->mutex[data->n_philos - 1 - 1];
            philos[i].ll_fork = data->n_philos - 1 - 1;
        }
        else
        {
            philos[i].l_fork = data->mutex[i - 1]; 
            philos[i].ll_fork = i - 1; 
        }
        philos[i].t_last_meal = -1;
        philos[i].meals = 0;
        philos[i].data = data;
        i++;
    }
}*/
























