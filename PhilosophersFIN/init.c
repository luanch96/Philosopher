/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisanch <luisanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:45:55 by luisanch          #+#    #+#             */
/*   Updated: 2024/08/15 18:40:27 by luisanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_input(t_philo *philo, char **argv)
{
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    philo->num_philosophers = ft_atoi(argv[1]);
    if(argv[5])
        philo->num_time_2_eat = ft_atoi(argv[5]);
    else
        philo->num_time_2_eat = -1;
}

void init_philosophers(t_philo *philos, t_program *program, pthread_mutex_t *forks, char **argv)
{
    int     i;

    i = 0;
    while(i < ft_atoi(argv[1]))
    {
        philos[i].id = i + 1;
        philos[i].eaters = 0;
        philos[i].meals = 0;
        init_input(&philos[i], argv);
        philos[i].start_time = get_time();
        philos[i].last_meal = get_time();
        philos[i].write_lock = &program->write_lock;
        philos[i].dead_lock = &program->dead_lock;
        philos[i].meal_lock = &program->meal_lock;
        philos[i].dead = &program->dead_flag;
        philos[i].left_fork = &forks[i];
        if(i == 0)
            philos[i].right_fork = &forks[philos[i].num_philosophers - 1];
        else
            philos[i].right_fork = &forks[i - 1];
        i++;
        
    }
}

void init_forks(pthread_mutex_t *forks, int philo_num)
{
    int i;
    
    i = 0;
    while(i < philo_num)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

void init_program(t_program *program, t_philo *philos)
{
    program->dead_flag = 0;
    program->philos = philos;
    pthread_mutex_init(&program->write_lock, NULL);
    pthread_mutex_init(&program->dead_lock, NULL);
    pthread_mutex_init(&program->meal_lock, NULL);
}
