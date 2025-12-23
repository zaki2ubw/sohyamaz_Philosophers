/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:13:42 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/20 18:58:39 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args	*config_info;

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
	if (parse_arguments(argc, argv, config_info) == 0)
		return (free(config_info), 1);
	printf("num_of_philos: %lu\n", config_info->num_of_philos);
	printf("ttdie: %lu\n", config_info->simulate_time[die_ms]);
	printf("tteat: %lu\n", config_info->simulate_time[eat_ms]);
	printf("ttsleep: %lu\n", config_info->simulate_time[sleep_ms]);
	printf("num_of_philo_must_eat: %lu\n", config_info->need_to_eat);
	//construct
	//create_threads
	//simulate
	//join_threads
	//destruct
	free(config_info);
	return (0);
}
