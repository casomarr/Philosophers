/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:23:22 by casomarr          #+#    #+#             */
/*   Updated: 2023/09/08 17:56:14 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Checks if all the philosophers are still alive and if the philosopher
sent to this function has eaten the amount of times necessary. If the 
nb_of_time_each_philo_must_eat was not specified in the command line, 
it will never be reached (set to -1 in init.c)*/
bool	conditions_check(t_thread *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->data->meals_counter_mutex);
	if (philo->meals_counter != \
	philo->data->number_of_times_each_philosopher_must_eat \
	&& philo->data->death == false)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_unlock(&philo->data->meals_counter_mutex);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_unlock(&philo->data->meals_counter_mutex);
		return (false);
	}
}

/*Checks if each philosopher has finished all its meals*/
bool	check_finished_all_meals(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->meals_counter_mutex);
		if (data->philo[i].meals_counter != \
		data->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_unlock(&data->meals_counter_mutex);
			return (false);
		}
		pthread_mutex_unlock(&data->meals_counter_mutex);
		i++;
	}
	return (true);
}

/*Checks if the philosopher sent to this function is dead by 
comparing its expected time of death to the current time. 
If current time > time of death, the philosopher is dead.*/
bool	check_death(t_thread *philo)
{
	pthread_mutex_lock(&philo->data->time_of_death_mutex);
	pthread_mutex_lock(&philo->data->nb_of_philo_mutex);
	pthread_mutex_lock(&philo->data->current_time_mutex);
	if (philo->time_of_death >= ft_current_time())
	{
		pthread_mutex_unlock(&philo->data->time_of_death_mutex);
		pthread_mutex_unlock(&philo->data->nb_of_philo_mutex);
		pthread_mutex_unlock(&philo->data->current_time_mutex);
		return (false);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->time_of_death_mutex);
		pthread_mutex_unlock(&philo->data->nb_of_philo_mutex);
		pthread_mutex_unlock(&philo->data->current_time_mutex);
		return (true);
	}
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			printf("Error : thread %d joined incorrectly\n", i);
			exit(1);
		}
		i++;
	}
	free(data->fork);
	free(data->philo);
	exit(0);
}
