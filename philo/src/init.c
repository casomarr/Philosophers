/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:19:17 by casomarr          #+#    #+#             */
/*   Updated: 2023/09/08 17:56:01 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Initializes the info for each philo*/
void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_thread) * data->number_of_philosophers);
	if (data->philo == NULL)
	{
		printf("Error in philo malloc\n");
		exit (0);
	}
	while (i < data->number_of_philosophers)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_counter = 0;
		data->philo[i].rfork = i;
		if (i == 0)
			data->philo[i].lfork = data->number_of_philosophers - 1;
		else
			data->philo[i].lfork = i - 1;
		data->philo[i].data = data;
		i++;
	}
}

/*Initializes all the other mutexes*/
void	init_mutex_2(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0 || \
	pthread_mutex_init(&data->meals_counter_mutex, NULL) != 0 || \
	pthread_mutex_init(&data->death_mutex, NULL) != 0 || \
	pthread_mutex_init(&data->time_of_death_mutex, NULL) != 0 || \
	pthread_mutex_init(&data->nb_of_philo_mutex, NULL) != 0 || \
	pthread_mutex_init(&data->current_time_mutex, NULL) != 0 || \
	pthread_mutex_init(&data->time_to_die_mutex, NULL) != 0 || \
	pthread_mutex_init(&data->start_time_mutex, NULL) != 0)
	{
		printf("Error while initializing mutex\n");
		exit (0);
	}
}

/*Initializes the mutex for each fork*/
void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_forks);
	if (data->fork == NULL)
	{
		printf("Error in fork malloc\n");
		exit (0);
	}
	while (i < (data)->number_of_forks)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
		{
			printf("Error while initializing fork mutex\n");
			free(data->philo);
			exit (0);
		}
		i++;
	}
	init_mutex_2(data);
}

/*Sets info from command line to the correspondant variables.
Nb_of_times_each_philo_must_eat : if not specified in command
line (argv[5]), set to -1 so that it is never reached by counter 
in function conditions_check() in stop.c
Initializes all the other variables (and sets them to 0/false).
*/
void	set_args(char **argv, t_data *data)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
		data->number_of_times_each_philosopher_must_eat = -1;
	else
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	data->number_of_forks = data->number_of_philosophers;
	data->death = false;
	data->finished_all_meals = false;
	init_philo(data);
	init_mutex(data);
}
