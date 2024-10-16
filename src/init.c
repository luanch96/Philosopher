/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luissanchez <luissanchez@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:45:55 by luisanch          #+#    #+#             */
/*   Updated: 2024/10/16 16:04:51 by luissanchez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_input(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_philosophers = ft_atoi(argv[1]);
	if (argv[5])
		philo->num_time_2_eat = ft_atoi(argv[5]);
	else
		philo->num_time_2_eat = -1;
	return ;
}

void	init_phi(t_philo *p, t_program *prog, pthread_mutex_t *fork, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		p[i].id = i + 1;
		p[i].eaters = 0;
		p[i].meals = 0;
		init_input(&p[i], av);
		p[i].start_time = get_time();
		p[i].last_meal = get_time();
		p[i].write_lock = &prog->write_lock;
		p[i].dead_lock = &prog->dead_lock;
		p[i].meal_lock = &prog->meal_lock;
		p[i].dead = &prog->dead_flag;
		p[i].left_fork = &fork[i];
		if (i == 0)
			p[i].right_fork = &fork[p[i].num_philosophers - 1];
		else
			p[i].right_fork = &fork[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
