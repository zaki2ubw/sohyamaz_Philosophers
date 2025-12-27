/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 13:47:07 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/27 18:59:03 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	start_simulation(t_table *table)
{
	uint64_t	delay;
	uint64_t	i;

	if (table == NULL)
		return (false);
	delay = table->config->headcount * 5 + MUST_WAIT;
	if (get_time_in_millisec(&table->sim_start_time) == false)
		return (false);
	table->sim_start_time = table->sim_start_time + delay;
	i = 0;
	if (table->config->headcount > 1)
	{
		if (pthread_create(&table->observer, NULL, \
			&monitor_routine, table) != 0)
			return (false);
	}
	while (i < table->config->headcount)
	{
		if (pthread_create(&table->philos[i]->thread_id, NULL, \
			&philo_routine, table->philos[i]) != 0)
			return (false);
		i++;
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
		pthread_join(table->philos[i]->thread_id, NULL);
		i++;
	}
	if (table->config->headcount > 1)
		pthread_join(table->observer, NULL);
	return ;
}
