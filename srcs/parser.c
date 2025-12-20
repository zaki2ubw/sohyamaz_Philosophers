/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:55:05 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/20 17:24:58 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	parse_args(const int argc, const char **argv, t_args *parsed_args)
{
	int	i;
	int	set_count;

	if (philo_atoi(argv[1], &parsed_args->num_of_philos) < 0)
		return (free(parsed_args), 0);
	i = 2;
	set_count = 0;
	while (set_count < sizeof(t_times))
	{
		if (philo_atoi(argv[i], &parsed_args->simulate_time[set_count]) < 0)
			return (free(parse_args), 0);
		i++;
		set_count++;
	}
	if (argc == 6 && philo_atoi(argv[5], &parsed_args->need_to_eat) < 0)
		return (free(parsed_args), 0);
	return (1);
}
