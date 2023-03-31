/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:56 by qtran             #+#    #+#             */
/*   Updated: 2023/03/31 18:55:45 by qtran            ###   ########.fr       */
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
	pthread_mutex_t	**mutex;
	int				forks;
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	struct timeval	get_t_of_day;
	long long		t_start;
	int n_meals; //number of times philo must eat
}					t_data;

typedef struct s_philo
{
	int				name;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				ll_fork;
	int				rr_fork;
	int t_last_meal; //timestamp
	int				meals;
	struct timeval	get_t_of_day;
	long long		timestamp_in_ms;
	t_data			*data;
}					t_philo;

//currently in main

void				create_threads(t_data *data, t_philo *philos);
// void	create_threads(t_data *data);
void				join_threads(t_data *data);
void				init_all_mutex(t_data *data);
void				destroy_all_mutex(t_data *data);

//init.c
void				init_data(char **av, t_data *data);
int					input_check(char **av);
void				init_one_pinoy_boy(t_data *data, t_philo *philos, int i);

//routine.c
void				*routine(void *philo);
void set_timestamp_in_ms(t_philo *ptr); //sets the timestamp relative to the start
void set_start_timestamp_in_ms(t_data *ptr);


//input_check.c
int					input_check(char **av);

//ft_atoi
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);

#endif