/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:03:10 by luisanch          #+#    #+#             */
/*   Updated: 2024/08/22 19:29:59 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_error_printing(char *str)
{
    int i;

    i = 0;
    i = printf("%s", str);
    return(i);
}

int ft_strlen (char *str)
{
    int i;

    i = 0;
    while(str[i] != '0')
        i++;
    return(i);
}

int	ft_atoi(char *str)
{
	unsigned long long	nb;
	int					sign;
	int					i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (sign * nb);
}

size_t get_time(void)
{
    struct timeval time;

    if(gettimeofday(&time, NULL) == -1)
		ft_error_printing("gettimeofday() error\n");
    return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

int ft_usleep (size_t miliseconds)
{
    size_t start;

    start = get_time();
    while((get_time() - start) < miliseconds)
        usleep(500);
    return(0);
}
