/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 10:39:29 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/27 12:10:38 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destruct_table(t_table *table)
{
	destruct_shared_mutex(table->shared, table->config->headcount);
	destruct_philos(table->philos, table->config->headcount);
	destruct_table(table);
	return ;
}

void	destruct_shared_mutex(t_resource *shared, uint64_t headcount)
{
	uint64_t	i;

	if (shared->is_flag_init == true)
		pthread_mutex_destroy(&shared->is_died_flag);
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

void	destruct_philos(t_philo **philos, uint64_t headcount)
{
	uint64_t	i;

	i = 0;
	while (i < headcount)
	{
		if (philos[i]->is_meal_init == true)
			pthread_mutex_destroy(&pthread_mutex_destroy[i]->meal_mutex);
		free(philos[i]);
		i++;
	}
	return ;
}

void	destruct_table(t_table *table)
{
	free(table->shared);
	free(table->philos);
	free(table->config);
	free(table);
	return ;
}
