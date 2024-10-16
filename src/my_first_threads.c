/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_first_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luissanchez <luissanchez@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:31:41 by luisanch          #+#    #+#             */
/*   Updated: 2024/10/16 16:19:57 by luissanchez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(char *str, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		ft_error_printing(str);
		ft_error_printing("\n");
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	while (i < program->philos[0].num_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	return ;
}

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo		*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat - 20);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

int	build_thread(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	watcher;
	int			i;

	if (pthread_create(&watcher, NULL, &monitor, program->philos) != 0)
		destroy ("Error craating thread", program, forks);
	i = 0;
	while (i < program->philos[0].num_philosophers)
	{
		if (pthread_create(&program->philos[i].thread, NULL, \
				&philo_routine, &program->philos[i]) != 0)
			destroy ("Error crating thread", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(watcher, NULL) != 0)
		destroy ("Error craating thread", program, forks);
	while (i < program->philos[0].num_philosophers)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destroy("Error crating thread", program, forks);
		i++;
	}
	return (EXIT_SUCCESS);
}
