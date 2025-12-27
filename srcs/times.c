/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:54:49 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/27 19:10:11 by sohyamaz         ###   ########.fr       */
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

void	take_short_sleep(uint64_t wait_ms)
{
	uint64_t	end_time;
	uint64_t	now;

	now = 0;
	if (get_time_in_millisec(&now) == false)
		return ;
	end_time = wait_ms + now;
	while (get_time_in_millisec(&now) < end_time)
	{
		usleep(100);
	}
	return ;
}
