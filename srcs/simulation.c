/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 13:47:07 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/28 14:52:04 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	start_simulation(t_table *table)
{
	uint64_t	i;

	if (table == NULL)
		return (false);
	if (set_sim_start_time(&table->sim_start_time, \
		table->config->headcount) == false)
		return (false);
	i = 0;
	while (i < table->config->headcount)
	{
		if (pthread_create(&table->philos[i]->thread_id, NULL, \
			&philo_routine, table->philos[i]) != 0)
			return (set_is_died_flag(table->shared, true), \
				stop_simulation(table), false);
		i++;
	}
	if (table->config->headcount > 1)
	{
		if (pthread_create(&table->observer, NULL, \
			&monitor_routine, table) != 0)
			return (set_is_died_flag(table->shared, true), \
				stop_simulation(table), false);
	}
	return (true);
}

void	stop_simulation(t_table *table)
{
	uint64_t	i;

	if (table == NULL)
		return ;
	i = 0;
	while (i < table->config->headcount)
	{
		if (table->philos[i]->thread_id != 0)
			pthread_join(table->philos[i]->thread_id, NULL);
		i++;
	}
	if (table->config->headcount > 1)
		pthread_join(table->observer, NULL);
	return ;
}
