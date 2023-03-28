/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:56:03 by qtran             #+#    #+#             */
/*   Updated: 2023/03/28 18:35:09 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <unistd.h>

static int check_if_numeric(char c)
{
    if ('0' <= c && c <= '9')
        return (1);
    return (0);
}


int input_check(char **av)
{
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (j == 0 && av[i][j] == '+')
                j++;
            else if (check_if_numeric(av[i][j]))
                j++;
            else
            {
                printf("Error input incorecct!\n");
                return (1);
            }
        }
        i++;
    }
    return (0);
}

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
    data->th = malloc(sizeof(pthread_t) * data->n_philos);
    data->mutex = malloc(sizeof(pthread_t) * data->n_philos);
}


void create_threads(t_data *data)
{
    char *err;
    int i;

    err = "Error, failed to create thread\n";
    i = 0;
    while (i < data->n_philos)
    {
        if (pthread_create(data->th[i], NULL, &routine, data) != 0)
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
        if (pthread_join(data->th[i], NULL) != 0);
            write(2, err, ft_strlen(err));
        i++;
        printf("Thread %d has finished execution\n", i);
    }
}
