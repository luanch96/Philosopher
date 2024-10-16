/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisanch <luisanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:03:10 by luisanch          #+#    #+#             */
/*   Updated: 2024/08/21 13:57:35 by luisanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_strlen (char *str)
{
    int i;

    i = 0;
    while(str[i] != '0')
        i++;
    return(i);
}

int ft_atoi(char *str)
{
    int result = 0;
    int sign = 1;
    
    while(*str == '-' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-')
        sign = -1;
    if(*str == '-'|| *str == '+')
        str++;
    while(*str >= '0' && *str <= '9')
        result = result * 10 + *str - '0';
        str++;
    return(sign * result);
}

size_t get_time(void)
{
    struct timeval time;
    
    if(gettimeofday(&time, NULL) == -1)
        write(2, "gettimeofday() error", 21);
    return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

int ft_usleep (size_t miliseconds)
{
    size_t start;

    start = get_time();
    while((get_time() - start) < miliseconds)
        ft_usleep(500);
    return(0);
}

int 

