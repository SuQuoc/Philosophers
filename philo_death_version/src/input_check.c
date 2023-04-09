/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:24:59 by qtran             #+#    #+#             */
/*   Updated: 2023/03/30 11:49:10 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

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