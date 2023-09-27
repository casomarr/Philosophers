/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:24:57 by casomarr          #+#    #+#             */
/*   Updated: 2023/09/08 16:36:02 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	arg_checks(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		printf("Error : wrong number of arguments");
		exit(1);
	}
	i = 1;
	while (i <= argc - 1)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) == false || ft_atoi(argv[i]) == 0)
			{
				printf("Error : argument is not a \
digit or is a negative number or is equal to 0");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;

	arg_checks(argc, argv);
	set_args(argv, &data);
	thread_creation(&data);
	return (0);
}
