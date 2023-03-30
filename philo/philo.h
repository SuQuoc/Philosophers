/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:56 by qtran             #+#    #+#             */
/*   Updated: 2023/03/30 14:09:09 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

//Structures

typedef struct s_data
{
	pthread_t		*th;
	//t_philo			*philos;
	pthread_mutex_t	*mutex;
	int				forks;
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int n_meals; //number of times philo must eat
}					t_data;

typedef struct s_philo
{
	int				name;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	int t_last_meal; //timestamp
	int				meals;
	t_data			*data;
}					t_philo;

//currently in main

void create_threads(t_data *data, t_philo *philos);
// void	create_threads(t_data *data);
void				join_threads(t_data *data);
void				init_all_mutex(t_data *data);
void				destroy_all_mutex(t_data *data);

//init.c
void				init_data(char **av, t_data *data);
int					input_check(char **av);
void				init_philos(t_data *data, t_philo *philos);

//routine.c
void				*routine(void *philo);

//input_check.c
int					input_check(char **av);

//ft_atoi
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);

#endif