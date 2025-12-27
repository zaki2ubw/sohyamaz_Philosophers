/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 02:31:06 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/27 14:53:03 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_table(t_args *parsed_args, t_table **table)
{
	*table = (t_table *)philo_calloc(1, sizeof(t_table));
	if (table == NULL)
		return (false);
	(*table)->config = parsed_args;
	if (init_table_vars(*table) == false)
		return (false);
	if (init_philos((*table)->philos, *table) == false)
		return (false);
	if (init_shared_mutex((*table)->shared, \
				(*table)->config->headcount) == false)
		return (false);
	return (true);
}

bool	init_table_vars(t_table *table)
{
	if (table == NULL)
		return (false);
	table->shared = (t_resource *)philo_calloc(1, sizeof(t_resource));
	if (table->shared == NULL)
		return (false);
	table->philos = \
		(t_philo **)philo_calloc(table->config->headcount, sizeof(t_philo *));
	if (table->philos == NULL)
		return (false);
	return (true);
}

bool	init_philos(t_philo **philo, t_table *table)
{
	uint64_t	i;

	if (philo == NULL || table == NULL)
		return (false);
	i = 0;
	while (i < table->config->headcount)
	{
		table->philos[i] = (t_philo *)philo_calloc(1, sizeof(t_philo));
		if (table->philos[i] == NULL)
			return (false);
		if (pthread_mutex_init(&table->philos[i]->meal_mutex, 0) != 0)
			return (false);
		table->philos[i]->is_meal_init = true;
		table->philos[i]->round = table;
		table->philos[i]->philo_id = i + 1;
		i++;
	}
	return (true);
}

bool	init_shared_mutex(t_resource *shared, uint64_t headcount)
{
	uint64_t	i;

	if (shared == NULL)
		return (false);
	shared->forks_array = \
		(pthread_mutex_t *)philo_calloc(headcount, sizeof(pthread_mutex_t));
	if (shared->forks_array == NULL)
		return (false);
	i = 0;
	while (i < headcount)
	{
		if (pthread_mutex_init(&shared->forks_array[i], 0) != 0)
			return (false);
		shared->forks_init_count = i;
		i++;
	}
	if (pthread_mutex_init(&shared->logger_mutex, 0) != 0)
		return (false);
	shared->is_logger_init = true;
	if (pthread_mutex_init(&shared->died_flag_mutex, 0) != 0)
		return (false);
	shared->is_died_mutex_init = true;
	shared->is_died_flag = false;
	return (true);
}
