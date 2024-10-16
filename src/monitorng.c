/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitorng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luissanchez <luissanchez@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:57:10 by luisanch          #+#    #+#             */
/*   Updated: 2024/10/16 16:14:57 by luissanchez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Funcion que usaremos para printear mensajes
void	print_text(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	if (!dead_loop(philo))
		printf ("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock (philo->write_lock);
	return ;
}

//Coprueba si filosofo se ha muerto
int	philo_death(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock (philo->meal_lock);
	if (get_time() - philo->last_meal >= time_to_die && philo->eaters == FALSE)
	{
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	}
	pthread_mutex_unlock (philo->meal_lock);
	return (EXIT_SUCCESS);
}

//¿HA MUERTO ALGUNO?
int	confirm_dead(t_philo *philo)
{
	int	a;

	a = 0;
	while (a < philo[0].num_philosophers)
	{
		if (philo_death(&philo[a], philo[a].time_to_die))
		{
			print_text ("died", &philo[a], philo[a].id);
			pthread_mutex_lock (philo[0].dead_lock);
			*philo->dead = 1;
			pthread_mutex_unlock (philo[0].dead_lock);
			return (EXIT_FAILURE);
		}
		a++;
	}
	return (EXIT_SUCCESS);
}

//Comprueba si los filosofos han consumido el numero total "meals"

int	check_if_nofood(t_philo *philo)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (philo[0].num_time_2_eat == -1)
		return (0);
	while (i < philo[0].num_philosophers)
	{
		pthread_mutex_lock (philo[i].meal_lock);
		if (philo[i].meals >= philo[i].num_time_2_eat)
			finished++;
		pthread_mutex_unlock (philo[i].meal_lock);
		i++;
	}
	if (finished == philo[0].num_philosophers)
	{
		pthread_mutex_lock (philo[0].dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock (philo[0].dead_lock);
		return (1);
	}
	return (0);
}

//funcion de observador, HILO
void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (TRUE)
	{
		if (confirm_dead(philos) == 1 || check_if_nofood(philos) == 1)
		{
			break ;
		}
	}
	return (pointer);
}
