/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:46:44 by casomarr          #+#    #+#             */
/*   Updated: 2023/09/08 16:56:56 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print(t_data *data, t_thread *philo, char activity)
{
	pthread_mutex_lock(&data->print_mutex);
	if (activity == 'F')
	{
		pthread_mutex_lock(&philo->data->current_time_mutex);
		printf("%ld %d has taken a fork\n", ft_current_time() \
		- data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->current_time_mutex);
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
	else if (activity == 'D')
	{
		pthread_mutex_lock(&philo->data->current_time_mutex);
		printf("%ld %d died\n", ft_current_time() - data->start_time, \
		philo->id);
		pthread_mutex_unlock(&philo->data->current_time_mutex);
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
	else
		ft_printf_2(data, philo, activity);
}

void	ft_printf_2(t_data *data, t_thread *philo, char activity)
{
	if (activity == 'E')
	{
		pthread_mutex_lock(&philo->data->current_time_mutex);
		printf("%ld %d is %s\n", ft_current_time() - data->start_time, \
		philo->id, "eating");
		pthread_mutex_unlock(&philo->data->current_time_mutex);
	}
	else if (activity == 'T')
	{
		pthread_mutex_lock(&philo->data->current_time_mutex);
		printf("%ld %d is %s\n", ft_current_time() - data->start_time, \
		philo->id, "thinking");
		pthread_mutex_unlock(&philo->data->current_time_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->data->current_time_mutex);
		printf("%ld %d is %s\n", ft_current_time() - data->start_time, \
		philo->id, "sleeping");
		pthread_mutex_unlock(&philo->data->current_time_mutex);
	}
	pthread_mutex_unlock(&data->print_mutex);
}

long int	ft_current_time(void)
{
	struct timeval	current_time;
	long int		current;

	gettimeofday(&current_time, NULL);
	current = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (current);
}
