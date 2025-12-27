/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 13:42:25 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/27 19:11:09 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *table_data)
{
	t_table	*table;

	if (table_data == NULL)
		return (NULL);
	table = (t_table *)table_data;
	if (wait_for_start_time(table->sim_start_time) == false)
		return (NULL);
	while (1)
	{
		if (is_sim_finished(table) == true)
			break ;
		take_short_sleep(1000);
	}
	return (NULL);
}

bool	is_sim_finished(t_table *table)
{
	bool		is_enough_meal;
	uint64_t	i;

	if (table == NULL)
		return (false);
	is_enough_meal = true;
	i = 0;
	while (i < table->config->headcount)
	{
		pthread_mutex_lock(&table->philos[i]->meal_mutex);
		if (is_philo_died(table->philos[i]) == true)
		{
			cremate_philo(table->shared, table->philos[i]);
			return (pthread_mutex_unlock(&table->philos[i]->meal_mutex), false);
		}
		if (table->config->num_of_must_eat > 0 && \
			table->philos[i]->ate_count < table->config->num_of_must_eat)
			is_enough_meal = false;
		pthread_mutex_unlock(&table->philos[i]->meal_mutex);
		i++;
	}
	if (is_enough_meal != true || table->config->num_of_must_eat == 0)
		return (set_is_died_flag(table->shared, false), false);
	set_is_died_flag(table->shared, true);
	return (true);
}

void	set_is_died_flag(t_resource *shared, bool flag)
{
	pthread_mutex_lock(&shared->died_flag_mutex);
	shared->is_died_flag = flag;
	pthread_mutex_unlock(&shared->died_flag_mutex);
	return ;
}

void	cremate_philo(t_resource *shared, t_philo *philo)
{
	set_is_died_flag(shared, true);
	print_log(shared, philo, DIED, true);
	return ;
}

bool	is_philo_died(t_philo *philo)
{
	uint64_t	now;

	if (philo == NULL)
		return (true);
	now = 0;
	if (get_time_in_millisec(&now) == false)
		return (true);
	pthread_mutex_lock(&philo->meal_mutex);
	if (now - philo->last_meal_time >= \
		philo->round->config->simulate_time[DIE_MS])
		return (true);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (false);
}
