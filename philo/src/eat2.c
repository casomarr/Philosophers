/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:30:51 by casomarr          #+#    #+#             */
/*   Updated: 2023/09/08 17:32:52 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	even_philo(t_thread *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->lfork]);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->death == true)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->lfork]);
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_print(philo->data, philo, 'F');
	pthread_mutex_lock(&philo->data->fork[philo->rfork]);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->death == true)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->lfork]);
		pthread_mutex_unlock(&philo->data->fork[philo->rfork]);
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_print(philo->data, philo, 'F');
	return (0);
}

int	odd_philo(t_thread *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->rfork]);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->death == true)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->rfork]);
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_print(philo->data, philo, 'F');
	pthread_mutex_lock(&philo->data->fork[philo->lfork]);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->death == true)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->lfork]);
		pthread_mutex_unlock(&philo->data->fork[philo->rfork]);
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_print(philo->data, philo, 'F');
	return (0);
}

void	one_philo(t_thread *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->rfork]);
	ft_print(philo->data, philo, 'F');
	while (philo->data->death == false)
	{
	}
	pthread_mutex_unlock(&philo->data->fork[philo->rfork]);
}
