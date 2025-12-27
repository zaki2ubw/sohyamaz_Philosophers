/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:31:33 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/27 19:08:32 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_resource *shared, t_philo *philo, \
		t_status status, bool is_died_notice)
{
	if (philo == NULL)
		return ;
	pthread_mutex_lock(&shared->logger_mutex);
	pthread_mutex_lock(&shared->died_flag_mutex);
	if (shared->is_died_flag == true && is_died_notice == false)
	{
		pthread_mutex_unlock(&shared->died_flag_mutex);
		return ;
	}
	pthread_mutex_unlock(&shared->died_flag_mutex);
	if (status == DIED)
		print_status(philo, "died");
	else if (status == EATING)
		print_status(philo, "is eating");
	else if (status == SLEEPING)
		print_status(philo, "is thinking");
	else if (status == TAKE_FORK_1 || status == TAKE_FORK_2)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&shared->logger_mutex);
	return ;
}

void	print_status(t_philo *philo, char *msg)
{
	uint64_t	timestamp;

	if (philo == NULL || msg == NULL)
		return ;
	timestamp = 0;
	if (get_time_in_millisec(&timestamp) == false)
		return ;
	timestamp = timestamp - philo->round->sim_start_time;
	printf("%ld %d %s\n", timestamp, philo->philo_id, msg);
	return ;
}
