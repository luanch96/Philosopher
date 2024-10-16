/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luissanchez <luissanchez@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:47:16 by luisanch          #+#    #+#             */
/*   Updated: 2024/08/22 20:20:16 by luissanchez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void think(t_philo *philo)
{
    print_message("is thinking", philo, philo->id);
}

void   sleep(t_philo *philo)
{
    print_message("is sleeping", philo, philo->id);
    ft_usleep(philo->time_to_sleep);
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    print_message("has taken fork", philo, philo->id);
    philo->eaters = 1;
    print_text("Phlilosopher is eating", philo, philo->id);
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = get_time();
    philo->meals++;
    pthread_mutex_unlock(philo->meal_lock);
    ft_usleep(philo->time_to_eat);
    philo->eaters = 0;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}