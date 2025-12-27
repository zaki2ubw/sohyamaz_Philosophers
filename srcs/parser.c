/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:55:05 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/27 13:42:36 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	parse_arguments(int argc, char **argv, t_args *parsed_args)
{
	uint64_t	set_count;
	int			i;

	if (philo_atoi(argv[1], &parsed_args->headcount) == 0)
		return (false);
	i = 2;
	set_count = 0;
	while (set_count < TIMESET_SIZE)
	{
		if (philo_atoi(argv[i], &parsed_args->simulate_time[set_count]) == 0)
			return (false);
		i++;
		set_count++;
	}
	parsed_args->num_of_must_eat = 0;
	if (argc == 5)
		parsed_args->num_of_must_eat = NO_SIM_LIMIT;
	else if (argc == 6)
	{
		if (*argv[5] == '0' || \
				philo_atoi(argv[5], &parsed_args->num_of_must_eat) == 0)
			return (false);
	}
	return (true);
}
