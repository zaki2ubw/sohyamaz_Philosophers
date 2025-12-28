/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:54:49 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/28 10:59:29 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_time_in_millisec(uint64_t *millisec)
{
	struct timeval	time;
	uint64_t		second;
	uint64_t		microsec;

	if (millisec == NULL)
		return (false);
	if (gettimeofday(&time, NULL) < 0)
		return (false);
	second = (uint64_t)time.tv_sec;
	microsec = (uint64_t)time.tv_usec;
	*millisec = second * 1000 + microsec / 1000;
	return (true);
}

bool	wait_for_start_time(uint64_t sim_start_time)
{
	uint64_t	now;

	now = 0;
	while (1)
	{
		if (get_time_in_millisec(&now) == false)
			return (false);
		if (now >= sim_start_time)
			break ;
	}
	return (true);
}

void	take_short_wait(uint64_t wait_ms)
{
	uint64_t	end_time;
	uint64_t	now;

	now = 0;
	if (get_time_in_millisec(&now) == false)
		return ;
	end_time = wait_ms + now;
	while (1)
	{
		if (get_time_in_millisec(&now) == false)
		   return ;
		if (now >= end_time)
			break ;
		usleep(100);
	}
	return ;
}

void	wait_until_finish_task(t_table *table, uint64_t task_term)
{
	uint64_t	limit;
	uint64_t	now;

	if (table == NULL)
		return ;
	now = 0;
	if (get_time_in_millisec(&now) == false)
		return ;
	limit = now + task_term;
	while (1)
	{
		if (get_time_in_millisec(&now) == false)
		   return ;
		if (now >= limit)
			break ;
		if (is_anyone_died(table) == true)
			break ;
		usleep(100);
	}
	return ;
}

