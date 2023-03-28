/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:56 by qtran             #+#    #+#             */
/*   Updated: 2023/03/28 18:36:54 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
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
	int				num;
    int             l_fork;
    int             r_fork;
	int				t_last_meal; //timestamp
	int				meals;
    t_data          *data;
}					t_philo;


//init.c
int					input_check(char **av);
void				create_threads(t_data *data);
void				join_threads(t_data *data);
void				init_all_mutex(t_data *data);
void				destroy_all_mutex(t_data *data);

//routine.c
void				*routine(t_data *data);

//ft_atoi
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);

#endif