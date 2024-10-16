/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luissanchez <luissanchez@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:45:49 by luisanch          #+#    #+#             */
/*   Updated: 2024/10/16 15:28:21 by luissanchez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void destroy_all(char *string, t_program *program, pthread_mutex_t *fork)
{
    int a;

    a = 0;
    if (string)
	{
		ft_error_printing(string);
        ft_error_printing("\n");
	}
    pthread_mutex_destroy(&program->dead_lock);
    pthread_mutex_destroy(&program->write_lock);
    pthread_mutex_destroy(&program->meal_lock);
    while(a < program->philos[0].num_philosophers)
	{
		pthread_mutex_destroy(&fork[a]);
        a++;
	}
}

int check_content(char *arg)
{
    int i;

    i = 0;
    while(arg[i] != '\0')
    {
        if(arg[i] < '0' || arg[i] > '9')
            return(1);
        i++;
    }
    return(0);
}

int check_nbr_args(char **argv)
{
    if (ft_atoi(argv[1]) > PHILO_MAX
            || ft_atoi(argv[1]) <= 0 || check_content(argv[1]))
            return (ft_error_printing("Invalid number philosophers\n"));
    if (ft_atoi(argv[2]) <= 0 || check_content(argv[2]) == 1)
            return (ft_error_printing("Invalid time to die\n"));
    if (ft_atoi(argv[3]) <= 0 || check_content(argv[3]) == 1)
            return (ft_error_printing("Invalid time to eat\n"));
    if (ft_atoi(argv[4]) <= 0 || check_content(argv[4]) == 1)
            return (ft_error_printing("Invalid dream time\n"));
    if (argv[5] && (ft_atoi(argv[5]) < 0 || check_content(argv[5]) == 1))
            return (ft_error_printing("Invalid meals\n"));
    return(0);
}

int main (int argc, char **argv)
{
    t_program   program;
    t_philo     philos[PHILO_MAX];
    pthread_mutex_t forks[PHILO_MAX];

    if (argc != 5 && argc != 6)
        return (ft_error_printing("Wrong argument nbr\n"));
    if (check_nbr_args(argv) == 1)
        return(1);
    init_program(&program, philos);
    init_forks(forks, ft_atoi(argv[1]));
    init_philosophers(philos, &program, forks, argv);
    build_thread(&program, forks);
    destroy_all(NULL, &program,forks);
    return(0);
}


//faaltan estos 3 x meter//