/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luissanchez <luissanchez@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:13:50 by luisanch          #+#    #+#             */
/*   Updated: 2024/10/16 16:24:19 by luissanchez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define PHILO_MAX 200
# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eaters;
	int				meals;
	int				num_philosophers;
	int				num_time_2_eat;
	int				*dead;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			start_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}						t_philo;

/*The program structure which holds all of the philosophers (in an array), 
//3 mutex, and one dead_flag, and the philo s
tructure where we have all of the general data*/

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

//main.c
int		check_nbr_args(char **argv);
int		check_content(char *arg);
void	destroy(char *string, t_program *program, pthread_mutex_t *fork);
int		ft_error_printing(char *str);

//init.c
void	init_input(t_philo *philo, char **argv);
void	init_phi(t_philo *p, t_program *prog, pthread_mutex_t *fork, char **av);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_program(t_program *program, t_philo *philos);

//utils.c
int		ft_strlen(char *str);
int		ft_atoi(char *str);
size_t	get_time(void);
int		ft_usleep(size_t miliseconds);

//my_first_threads.c
void	destroy_all(char *str, t_program *program, pthread_mutex_t *forks);
int		dead_loop(t_philo *philo);
void	*philo_routine(void *pointer);
int		build_thread(t_program *program, pthread_mutex_t *forks);

//Actions -> activity_philos
void	think(t_philo *philo);
void	dream(t_philo *philo);
void	eat(t_philo *philo);

//moitoring
void	*monitor(void *pointer);
int		confirm_dead(t_philo *philo);
int		philo_death(t_philo *philo, size_t time_to_die);
void	print_text(char *str, t_philo *philo, int id);
int		check_if_nofood(t_philo *philo);

#endif