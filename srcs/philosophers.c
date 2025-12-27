/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:25:37 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/27 20:15:35 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *philo_data)
{
	t_philo	*philo;

	if (philo_data == NULL)
		return (NULL);
	philo = (t_philo *)philo_data;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = philo->round->sim_start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->round->config->headcount == 1)
		return (philo_must_die(philo));
	if (philo->philo_id % 2 != 0)
		take_short_wait(1000);
	while (is_anyone_died(philo->round) == false)
	{
		eat_and_sleep_time(philo);
		thinking_time(philo);
	}
	return (NULL)
}

void	eat_and_sleep_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->round->forks_array[philo[primary_fork]]);
	print_log(philo->round->shared, philo, TAKE_FORK_1, false);
	pthread_mutex_lock(&philo->round->forks_array[philo[secondary_fork]]);
	print_log(philo->round->shared, philo, TAKE_FORK_2, false);
	print_log(philo->round->shared, philo, EATING, false);
	pthread_mutex_lock(&philo->meal_mutex);
	if (get_time_in_millisec(&philo->last_meal_time) == false)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	//philosleep@philosopher.c:30
	take_short_wait();

void	*philo_must_die(t_philo *philo)
{
	if (philo == NULL)
		return (NULL);
	pthread_mutex_lock(&philo->round->shared->forks_array[philo->primary_fork]);
	print_log(philo->round->shared, philo, TAKE_FORK_1, false);
	take_short_wait(philo->round->config->simulate_time[DIE_MS]);
	print_log(philo->round->shared, philo, DIED, true);
	pthread_mutex_unlock(&philo->round->shared->\
		forks_array[philo->primary_fork]);
	return (NULL);
}

bool	is_anyone_died(t_table *table)
{
	bool	is_died;

	if (table == NULL || table->shared == NULL)
		return (true);
	pthread_mutex_lock(&table->shared->died_flag_mutex);
	is_died = table->shared->is_died_flag;
	pthread_mutex_unlock(&table->shared->died_flag_mutex);
	return (is_died);
}
