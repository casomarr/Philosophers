/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:39:13 by casomarr          #+#    #+#             */
/*   Updated: 2023/09/08 17:55:40 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_thread
{
	int					id;
	pthread_t			thread;
	unsigned int		meals_counter;
	long int			time_of_death;
	int					lfork;
	int					rfork;
	t_data				*data;
}	t_thread;

typedef struct s_data
{
	int				number_of_philosophers;
	long int		time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	unsigned int	number_of_times_each_philosopher_must_eat;
	int				number_of_forks;
	bool			death;
	long int		start_time;
	bool			finished_all_meals;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meals_counter_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	time_of_death_mutex;
	pthread_mutex_t	nb_of_philo_mutex;
	pthread_mutex_t	current_time_mutex;
	pthread_mutex_t	time_to_die_mutex;
	pthread_mutex_t	start_time_mutex;
	pthread_mutex_t	*fork;
	t_thread		*philo;
}	t_data;

/*MAIN*/
void		arg_checks(int argc, char **argv);

/*INIT*/
void		init_philo(t_data *data);
void		init_mutex(t_data *data);
void		init_mutex_2(t_data *data);
void		set_args(char **argv, t_data *data);

/*THREADS*/
void		part2(t_thread *philo);
bool		death_check_unlock(t_thread *philo);
void		routine_check_death(t_data *data);
void		*routine(void *arg);
void		thread_creation(t_data *data);

/*UTILS*/
bool		ft_isdigit(int c);
int			ft_atoi(char *nptr);

/*EAT*/
void		philo_eating(t_thread *philo);
void		philo_eating_2(t_thread *philo);
void		philo_eating_3(t_thread *philo, int mutex);

/*EAT2*/
int			even_philo(t_thread *philo);
int			odd_philo(t_thread *philo);
void		one_philo(t_thread *philo);

/*PRINT*/
void		ft_print(t_data *data, t_thread *philo, char activity);
void		ft_printf_2(t_data *data, t_thread *philo, char activity);
long int	ft_current_time(void);

/*STOP*/
bool		conditions_check(t_thread *philo);
bool		check_finished_all_meals(t_data *data);
bool		check_death(t_thread *philo);
void		ft_free(t_data *data);

#endif