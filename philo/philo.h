/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:56 by qtran             #+#    #+#             */
/*   Updated: 2023/04/14 16:50:43 by qtran            ###   ########.fr       */
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
	pthread_mutex_t	death_lock;
	pthread_mutex_t	time_print_lock;
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				death_bool;
	long long		t_start_in_ms;
	int				n_meals;
}					t_data;

typedef struct s_philo
{
	int				name;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	int				meals;
	int				time_to_die;
	long long		t_start_in_ms;
	long long		t_in_ms;
	long long		last_meal;
	unsigned int	timestamp;
	t_data			*data;
}					t_philo;

//main.c
void				protected_print(t_philo *philo, char *msg);

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
int					check_if_full_from_eating(t_philo *philo);

//routine_2.c
void				philo_eats(t_philo *philo, pthread_mutex_t *first,
						pthread_mutex_t *sec);
void				grab_first_fork_if_w_grab_second(t_philo *philo,
						pthread_mutex_t *first,
						pthread_mutex_t *sec);
void				give_forks_back(pthread_mutex_t *first,
						pthread_mutex_t *sec);
void				philo_sleeps(t_philo *philo);
void				protected_print(t_philo *philo, char *msg);

//time_utils.c
void				get_time_in_ms(long long *time_in_ms);
void				set_rel_timestamp(t_philo *philo);

//death_things.c
int					all_alive(t_data *ptr);
void				*look_if_died(void *ptr);
int					all_alive2(t_data *ptr);

//input_check.c
int					input_check(char **av);
int					check_lonely_philo_main(char **av);

//others
long long int		ft_atoi(const char *str);
size_t				ft_strlen(const char *s);

#endif