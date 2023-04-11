/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:18:33 by qtran             #+#    #+#             */
/*   Updated: 2023/04/11 17:39:07 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void philo_sleeps(t_philo *philo)
{
    protected_print(philo, "is sleeping");
    usleep(philo->data->t_sleep * 1000);
}


void philo_eats(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *sec)
{
    int eating_time;

    //if (all_alive2(philo->data) == 0)
    //    return ;
        
    grab_first_fork_if_w_grab_second(philo, first, sec);
    protected_print(philo, "is eating");
    
    pthread_mutex_lock(&philo->data->time_print_lock);
    set_rel_timestamp(philo);
    philo->last_meal = philo->t_in_ms;
    eating_time = philo->data->t_eat;
    pthread_mutex_unlock(&philo->data->time_print_lock);
    
    usleep(eating_time * 1000);

    pthread_mutex_lock(&philo->data->death_lock);
    philo->meals++;
    pthread_mutex_unlock(&philo->data->death_lock);

    //pthread_mutex_lock(&philo->data->time_print_lock);
    //set_rel_timestamp(philo);
    //philo->last_meal = philo->t_in_ms;
    //philo->meals++;
    //pthread_mutex_unlock(&philo->data->time_print_lock);

    give_forks_back(first, sec);
}

void grab_first_fork_if_w_grab_second(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *sec)
{
    //if (all_alive2(philo->data) == 0)
        //return ;

    pthread_mutex_lock(first);
    pthread_mutex_lock(sec);
    if (all_alive2(philo->data))
    {
        pthread_mutex_lock(&philo->data->time_print_lock);
        set_rel_timestamp(philo);
        printf("%u %d has taken fork\n", philo->timestamp, philo->name);
        set_rel_timestamp(philo);
        printf("%u %d has taken fork\n", philo->timestamp, philo->name);
        pthread_mutex_unlock(&philo->data->time_print_lock);
    }
}

void give_forks_back(pthread_mutex_t *first, pthread_mutex_t *sec)
{
    pthread_mutex_unlock(sec);
    pthread_mutex_unlock(first);
}

int check_if_full_from_eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->death_lock);
    if (philo->data->n_meals > 0 && philo->meals == philo->data->n_meals)
    {
        pthread_mutex_unlock(&philo->data->death_lock);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->death_lock);
    return (0);
}


int check_lonely_philo(t_philo *philo)
{
    if (philo->data->n_philos == 1)
    {
        printf("%d 1 died\n", philo->data->t_die);
        return (1);
    }
    return (0);
}

void *routine(void *ptr)
{
    t_philo *philo;
    pthread_t death_checker;
    
    philo = (t_philo *)ptr;
    if (check_lonely_philo(philo))
        return (NULL);
    pthread_create(&death_checker, NULL, &look_if_died, philo);
    while(all_alive2(philo->data))
    {
        if (philo->name % 2 != 0)
        {
            philo_eats(philo, philo->r_fork, philo->l_fork);
            if (check_if_full_from_eating(philo))
                return NULL;
            philo_sleeps(philo);
            protected_print(philo, "is thinking");
        }
        else
        {
            usleep(1000);
            philo_eats(philo, philo->l_fork, philo->r_fork);
            if (check_if_full_from_eating(philo))
                return NULL;
            philo_sleeps(philo);
            protected_print(philo, "is thinking");
        }
    }
    pthread_join(death_checker, NULL);
    return (NULL);
}
//pthread_detach(death_checker);








