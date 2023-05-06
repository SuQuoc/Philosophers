/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_odd_even.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:54:24 by qtran             #+#    #+#             */
/*   Updated: 2023/04/27 11:00:58 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_odd_threads(t_data *data, t_philo *philos)
{
	int		i;
	char	*err;

	err = "Error, failed to create thread\n";
	i = 0;
	while (i < data->n_philos)
	{
		init_one_pinoy_boy(data, philos, i);
		if (pthread_create(&data->th[i], NULL, &routine, &philos[i]) != 0)
		{
			write(2, err, ft_strlen(err));
			join_n_threads_odd(data, i);
			return (1);
		}
		i += 2;
	}
	return (0);
}

//checks for even but i use arrays the actual thread is an odd number
int	join_n_threads_odd(t_data *data, int n)
{
	int		i;
	char	*err;

	err = "Error, failed to join thread\n";
	i = 0;
	while (i < n)
	{
		if (i % 2 == 0)
		{
			if (pthread_join(data->th[i], NULL) != 0)
			{
				write(2, err, ft_strlen(err));
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	create_even_threads(t_data *data, t_philo *philos)
{
	int		i;
	char	*err;

	err = "Error, failed to create thread\n";
	i = 1;
	while (i < data->n_philos)
	{
		init_one_pinoy_boy(data, philos, i);
		if (pthread_create(&data->th[i], NULL, &routine, &philos[i]) != 0)
		{
			write(2, err, ft_strlen(err));
			join_n_threads_odd(data, data->n_philos);
			join_n_threads_even(data, i);
			return (1);
		}
		i += 2;
	}
	return (0);
}

int	join_n_threads_even(t_data *data, int n)
{
	int		i;
	char	*err;

	err = "Error, failed to join thread\n";
	i = 1;
	while (i < n)
	{
		if (pthread_join(data->th[i], NULL) != 0)
		{
			write(2, err, ft_strlen(err));
			return (1);
		}
		i += 2;
	}
	return (0);
}
