/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 14:08:24 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/28 14:15:03 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_is_died_flag(t_resource *shared, bool flag)
{
	pthread_mutex_lock(&shared->died_flag_mutex);
	shared->is_died_flag = flag;
	pthread_mutex_unlock(&shared->died_flag_mutex);
	return ;
}

bool	is_anyone_died(t_table *table)
{
	bool	is_died;

	if (table == NULL || table->shared == NULL)
		return (true);
	pthread_mutex_lock(&table->shared->died_flag_mutex);
	is_died = table->shared->is_died_flag;
	pthread_mutex_unlock(&table->shared->died_flag_mutex);
	if (is_died == true)
		return (is_died);
	return (false);
}

void	*philo_must_die(t_philo *philo)
{
	if (philo == NULL)
		return (NULL);
	pthread_mutex_lock(&philo->round->shared->forks_array[philo->primary_fork]);
	print_log(philo->round->shared, philo, TAKE_FORK_1, false);
	take_short_wait(philo->round->config->simulate_time[DIE_MS]);
	set_is_died_flag(philo->round->shared, true);
	print_log(philo->round->shared, philo, DIED, true);
	pthread_mutex_unlock(&philo->round->shared->\
		forks_array[philo->primary_fork]);
	return (NULL);
}
