/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:11:32 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/20 18:50:05 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

typedef enum	e_timeset
{
	die_ms,
	eat_ms,
	sleep_ms,
}	sim_timeset;

typedef struct	s_args
{
	uint64_t	num_of_philos;
	uint64_t	simulate_time[sizeof(sim_timeset)];
	uint64_t	need_to_eat;
} t_args;

typedef struct	s_philo
{
	unsigned int	philo_id;
	pthread_mutex_t	*primary_fork;
	pthread_mutex_t	*secondary_fork;
	t_philo			*prev;
	bool			arrive;
} t_philo;

typedef struct	s_mutex;
{
	pthread_mutex_t	**forks_array;
	pthread_mutex_t	*log_mutex;
} t_mutex;

typedef struct	s_observer
{
	bool	everyone_on_the_table;



//parser
bool	parse_arguments(int argc, char **argv, t_args *parsed_args);

//philo_util
bool	philo_atoi(const char *origin_str, uint64_t *converted_num);
bool	philo_strlen(const char *str, size_t *len);
bool	is_valid_number(char c);
void	*philo_calloc(size_t mem_byte, size_t mem_size);

#endif
