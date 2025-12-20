/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:13:42 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/20 18:32:10 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: You need to give 4 or 5 arguments to ./philo\n");
		printf("usage: ./philo num_of_philo\
			ttdie tteat ttsleep [num_of_philo_must_eat]\n");
		return (1);
	}
	printf("given arguments are %s, %s, %s, %s\n",
			argv[1],
			argv[2],
			argv[3],
			argv[4]);
	config_info = (t_args *)philo_calloc(1, sizeof(t_args));
	if (config_info == NULL)
		return (1);
	//perse
	if (parse_args(argc, argv, config_info) == 0)
		return (free(config_info), 1);
	//construct
	//create_threads
	//simulate
	//join_threads
	//destruct
	return (0);
}
