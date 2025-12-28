/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 10:39:29 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/28 14:58:46 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destruct_shared_mutex(t_resource *shared);
static void	destruct_philos(t_philo **philos, uint64_t headcount);
static void	destruct_table_vars(t_table *table);

void	destruct_table(t_table *table)
{
	if (table == NULL)
		return ;
	destruct_shared_mutex(table->shared);
	destruct_philos(table->philos, table->config->headcount);
	destruct_table_vars(table);
	free(table);
	return ;
}

static void	destruct_shared_mutex(t_resource *shared)
{
	uint64_t	i;

	if (shared == NULL)
		return ;
	if (shared->is_died_mutex_init == true)
		pthread_mutex_destroy(&shared->died_flag_mutex);
	if (shared->is_logger_init == true)
		pthread_mutex_destroy(&shared->logger_mutex);
	i = 0;
	while (i < shared->forks_init_count)
	{
		pthread_mutex_destroy(&shared->forks_array[i]);
		i++;
	}
	free(shared->forks_array);
	return ;
}

static void	destruct_philos(t_philo **philos, uint64_t headcount)
{
	uint64_t	i;

	i = 0;
	if (philos == NULL)
		return ;
	while (i < headcount)
	{
		if (philos[i] == NULL)
			break ;
		if (philos[i]->is_meal_init == true)
			pthread_mutex_destroy(&philos[i]->meal_mutex);
		free(philos[i]);
		i++;
	}
	return ;
}

static void	destruct_table_vars(t_table *table)
{
	free(table->shared);
	free(table->philos);
	table->philos = NULL;
	table->config = NULL;
	table->shared = NULL;
	return ;
}
