/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:18:21 by carolina          #+#    #+#             */
/*   Updated: 2023/09/08 17:34:31 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*First, checks if there is only one philosopher (yes = death).
If not, checks the number of philosophers. If odd number, splits 
the philosophers into three goups and desinchronizes them (the first
philosopher will wait 0sec, the evens 1 sec and the odds 2 sec) so 
that they all get to eat.
Then sends all the philosophers to even_philo() or odd_philo() whose
only difference is to make them start with a different fork.*/
void	philo_eating(t_thread *philo)
{
	int	mutex;

	philo_eating_2(philo);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->death == true)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (philo->id % 2 == 0)
		mutex = even_philo(philo);
	else
		mutex = odd_philo(philo);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->death == true && mutex == 0)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->lfork]);
		pthread_mutex_unlock(&philo->data->fork[philo->rfork]);
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
	philo_eating_3(philo, mutex);
}

void	philo_eating_2(t_thread *philo)
{
	if (philo->data->number_of_philosophers == 1)
	{
		one_philo(philo);
		return ;
	}
	else
	{
		if (philo->data->number_of_philosophers % 2 != 0)
		{
			if (philo->id % 2 == 0)
				usleep(1000);
			else if (philo->id % 2 != 0 && philo->id != 1)
				usleep(2000);
		}
	}
}

void	philo_eating_3(t_thread *philo, int mutex)
{
	if (mutex == 1)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_print(philo->data, philo, 'E');
	pthread_mutex_lock(&philo->data->time_of_death_mutex);
	pthread_mutex_lock(&philo->data->time_to_die_mutex);
	pthread_mutex_lock(&philo->data->current_time_mutex);
	philo->time_of_death = ft_current_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->time_of_death_mutex);
	pthread_mutex_unlock(&philo->data->current_time_mutex);
	pthread_mutex_unlock(&philo->data->time_to_die_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data->meals_counter_mutex);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->data->meals_counter_mutex);
	pthread_mutex_unlock(&philo->data->fork[philo->lfork]);
	pthread_mutex_unlock(&philo->data->fork[philo->rfork]);
}
