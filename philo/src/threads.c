/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:18:30 by carolina          #+#    #+#             */
/*   Updated: 2023/09/08 17:39:24 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Function that constantly lops over the philosophers' info to check
their death. That's how we avoid having a large delay between the death 
of a philosopher and the moment the program stops.
This function loops while the threads are in their routine : once the threads
are created in thread_creation() the program runs over the next lines, it does
not have to wait for the threads to leave the routine to continue.*/
void	routine_check_death(t_data *data)
{
	int	i;

	i = 0;
	while (data->death == false && data->finished_all_meals == false)
	{
		pthread_mutex_lock(&data->nb_of_philo_mutex);
		if (i == data->number_of_philosophers)
			i = 0;
		pthread_mutex_unlock(&data->nb_of_philo_mutex);
		if (check_finished_all_meals(data) == true)
		{
			data->finished_all_meals = true;
			return ;
		}
		if (check_death(&(data)->philo[i]) == true)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->death = true;
			pthread_mutex_unlock(&data->death_mutex);
			ft_print(data, &(data)->philo[i], 'D');
		}
		i++;
	}
}

bool	death_check_unlock(t_thread *philo)
{
	if (philo->data->death == true)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (true);
	}
	return (false);
}

/*Function that send each philosopher to eat/sleep/think.
The usleep(125) is used to give some air to the mutexes every
time they finish a loop, otherwise they bug sometimes.*/
void	*routine(void *arg)
{
	t_thread	*philo;

	philo = (t_thread *)arg;
	pthread_mutex_lock(&philo->data->start_time_mutex);
	pthread_mutex_unlock(&philo->data->start_time_mutex);
	while (conditions_check(philo) == true)
	{
		if (philo->id % 2)
			usleep(125);
		pthread_mutex_lock(&philo->data->death_mutex);
		if (death_check_unlock(philo) == true)
			break ;
		pthread_mutex_unlock(&philo->data->death_mutex);
		philo_eating(philo);
		pthread_mutex_lock(&philo->data->death_mutex);
		if (death_check_unlock(philo) == true)
			break ;
		part2(philo);
		if (death_check_unlock(philo) == true)
			break ;
		pthread_mutex_unlock(&philo->data->death_mutex);
		ft_print(philo->data, philo, 'T');
	}
	return ((void *)0);
}

void	part2(t_thread *philo)
{
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_print(philo->data, philo, 'S');
	usleep(philo->data->time_to_sleep * 1000);
	pthread_mutex_lock(&philo->data->death_mutex);
}

/*Function that creates and sends each thread into the routine function.
The start_time_mutex is locked here and in the routine while the 
philosophers (= the theads) are ceated. Otherwise, if there is a large 
number of philosophers, the first and the last would not have the same 
start_time (there would be a delay).*/
void	thread_creation(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->start_time_mutex);
	data->start_time = ft_current_time();
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philo[i].time_of_death = data->start_time + data->time_to_die;
		if (pthread_create(&(data->philo[i].thread), NULL, routine, \
		(void *)&(data->philo[i])) != 0)
		{
			printf("Error : thread created incorrectly\n");
			exit(1);
		}
		i++;
	}
	pthread_mutex_unlock(&data->start_time_mutex);
	routine_check_death(data);
	ft_free(data);
}
