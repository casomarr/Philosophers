/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolina <carolina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:29:57 by casomarr          #+#    #+#             */
/*   Updated: 2023/07/20 19:12:35 by carolina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	else
		return (false);
}

int	ft_atoi(char *nptr)
{
	int				nb;
	unsigned int	i;
	unsigned int	negative;

	i = 0;
	nb = 0;
	negative = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			negative = 1;
		if (nptr[i + 1] == '+' || nptr[i + 1] == '-')
			return (0);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	if (negative == 1)
		nb = nb * (-1);
	return (nb);
}
