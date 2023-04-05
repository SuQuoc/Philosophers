/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:56 by qtran             #+#    #+#             */
/*   Updated: 2023/04/05 14:08:11 by qtran            ###   ########.fr       */
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
	pthread_mutex_t	**fork;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*t_start_lock;
	int				forks;
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int 			death_bool;
	long long		t_start_in_ms;
	int n_meals; //number of times philo must eat
}					t_data;

typedef struct s_philo
{
	int				name;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				ll_fork;
	int				rr_fork;
	int				meals;
	int				time_to_die;
	long long		t_in_ms;
	long long		last_meal; //timestamp dh. von start abgezogen
	long long		timestamp; //t_start - t_in_ms; only for printing
	t_data			*data;
}					t_philo;




//threads and mutex
void				create_threads(t_data *data, t_philo *philos);
void				join_threads(t_data *data);
void				destroy_all_mutex(t_data *data);

//init.c
void				init_all_fork_mutex(t_data *data);
void				init_data(char **av, t_data *data);
int					input_check(char **av);
void				init_one_pinoy_boy(t_data *data, t_philo *philos, int i);

//routine.c
void				*routine(void *philo);
//void set_start_timestamp_in_ms(t_data *ptr);



//time_utils.c
void get_time_in_ms(long long *time_in_ms); //sets the timestamp relative to the start
void set_rel_timestamp(t_philo *philo);



//death_things.c
int all_alive(t_data *ptr);
void check_death(t_philo *philo);
void *look_if_died(void *ptr);



//input_check.c
int					input_check(char **av);

//ft_atoi
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);

#endif