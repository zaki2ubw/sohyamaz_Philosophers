/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:13:42 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/27 18:43:19 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	t_args	*parsed_args;

	if (argc != 5 && argc != 6)
	{
		printf("Error: You need to give 4 or 5 arguments to ./philo\n");
		printf("usage: ./philo num_of_philo\
 ttdie tteat ttsleep [num_of_philo_must_eat]\n");
		return (1);
	}
	parsed_args = (t_args *)philo_calloc(1, sizeof(t_args));
	if (parsed_args == NULL)
		return (1);
	if (parse_arguments(argc, argv, parsed_args) == false)
		return (free(parsed_args), 1);
	if (init_table(parsed_args, &table) == false)
		return (free(parsed_args), destruct_table(table), 1);
	if (start_simulation(table) == false)
		return (free(parsed_args), destruct_table(table), 1);
	stop_simulation(table);
	destruct_table(table);
	free(parsed_args);
	return (0);
}
