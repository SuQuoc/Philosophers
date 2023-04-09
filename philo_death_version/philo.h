/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:56 by qtran             #+#    #+#             */
/*   Updated: 2023/04/07 17:19:57 by qtran            ###   ########.fr       */
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
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_lock; //for death bool
	pthread_mutex_t	time_print_lock; //for t_start_in_ms was jedes mal abgerufen wird wenn print
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
	int				meals;
	int				time_to_die;
	long long		t_start_in_ms;
	long long		t_in_ms;
	long long		last_meal; //timestamp dh. von start abgezogen
	unsigned int	timestamp; //t_start - t_in_ms; only for printing
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
void give_forks_back(pthread_mutex_t *first, pthread_mutex_t *sec);

//void set_start_timestamp_in_ms(t_data *ptr);



//time_utils.c
void get_time_in_ms(long long *time_in_ms); //sets the timestamp relative to the start
void set_rel_timestamp(t_philo *philo);
void philo_eats(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *sec);
void grab_first_fork_if_w_grab_second(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *sec);


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