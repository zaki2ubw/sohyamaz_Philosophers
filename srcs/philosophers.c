/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:25:37 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/28 14:36:59 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking_time(t_philo *philo);
static void	eat_and_sleep_time(t_philo *philo);
static bool	eat_sequence(t_philo *philo);
static void	sleep_sequence(t_philo *philo);

void	*philo_routine(void *philo_data)
{
	t_philo	*philo;

	if (philo_data == NULL)
		return (NULL);
	philo = (t_philo *)philo_data;
	if (wait_for_start_time(philo->round->sim_start_time) == false)
		return (NULL);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = philo->round->sim_start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->round->config->headcount == 1)
		return (philo_must_die(philo));
	if (philo->philo_id % 2 != 0)
		take_short_wait(philo->round->config->simulate_time[EAT_MS] / 2);
	while (is_anyone_died(philo->round) == false)
	{
		eat_and_sleep_time(philo);
		thinking_time(philo);
	}
	return (NULL);
}

static void	thinking_time(t_philo *philo)
{
	uint64_t	thinkable_time;
	uint64_t	current_starv;
	uint64_t	now;
	uint64_t	ttdie;
	uint64_t	tteat;

	if (philo == NULL)
		return ;
	if (get_time_in_millisec(&now) == false)
		return ;
	current_starv = now - philo->last_meal_time;
	ttdie = philo->round->config->simulate_time[DIE_MS];
	tteat = philo->round->config->simulate_time[EAT_MS];
	if (ttdie > current_starv && (ttdie - current_starv) > tteat)
		thinkable_time = (ttdie - tteat - current_starv) / 2;
	else
		thinkable_time = 0;
	if (thinkable_time > 600)
		thinkable_time = 200;
	print_log(philo->round->shared, philo, THINKING, false);
	wait_until_finish_task(philo->round, thinkable_time);
	return ;
}

static void	eat_and_sleep_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->round->\
		shared->forks_array[philo->primary_fork]);
	print_log(philo->round->shared, philo, TAKE_FORK_1, false);
	pthread_mutex_lock(&philo->round->\
		shared->forks_array[philo->secondary_fork]);
	print_log(philo->round->shared, philo, TAKE_FORK_2, false);
	if (eat_sequence(philo) == false)
	{
		pthread_mutex_unlock(&philo->round->\
			shared->forks_array[philo->secondary_fork]);
		pthread_mutex_unlock(&philo->round->\
			shared->forks_array[philo->primary_fork]);
		return ;
	}
	pthread_mutex_unlock(&philo->round->\
		shared->forks_array[philo->secondary_fork]);
	pthread_mutex_unlock(&philo->round->\
		shared->forks_array[philo->primary_fork]);
	sleep_sequence(philo);
	return ;
}

static bool	eat_sequence(t_philo *philo)
{
	if (philo == NULL)
		return (false);
	print_log(philo->round->shared, philo, EATING, false);
	pthread_mutex_lock(&philo->meal_mutex);
	if (get_time_in_millisec(&philo->last_meal_time) == false)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	wait_until_finish_task(philo->round, \
		philo->round->config->simulate_time[EAT_MS]);
	if (is_anyone_died(philo->round) == true)
		return (false);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->ate_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (true);
}

static void	sleep_sequence(t_philo *philo)
{
	if (philo == NULL)
		return ;
	print_log(philo->round->shared, philo, SLEEPING, false);
	wait_until_finish_task(philo->round, \
		philo->round->config->simulate_time[SLEEP_MS]);
	return ;
}
