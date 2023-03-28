/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:05:17 by qtran             #+#    #+#             */
/*   Updated: 2022/12/30 16:48:02 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

/* int main()
{
	//Testing Newline at the end
	char *newline = "      -283648\n";
	printf("Newline test: %d\n", atoi(newline));

	char *min = "      -2147483648";
	printf("min test: %d\n", atoi(min));

	char *max = "		2147483647";
	printf("Max test: %d\n\n", atoi(max));

	char *lmin = "		-2147483651";
	printf("long min test: %d\n", atoi(lmin));

	char *lmax = "		9223372036854775";
	printf("long max test: %d\n\n", atoi(lmax));

	char *llmin = "		-9223372036854775808";
	printf("longlong min test: %d\n", atoi(llmin));

	char *llmax = "		9223372036854775807"; //19 stellen
	printf("longlong max test: %d\n\n", atoi(llmax));

	char *test = "		9223372036854775801";
	printf("test test: %d\n\n", atoi(test));

	return (0);
} */