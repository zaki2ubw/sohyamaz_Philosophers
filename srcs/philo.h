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
# include <pthread.h>

typedef enum e_timeset	t_timeset;
typedef struct s_args	t_args;
typedef struct s_philo	t_philo;
typedef struct s_resource	t_resource;
typedef struct s_table	t_table;

enum	e_timeset
{
	DIE_MS = 0,
	EAT_MS = 1,
	SLEEP_MS = 2,
	TIMESET_SIZE = 3
};

struct	s_args
{
	uint64_t	num_of_philos;
	uint64_t	simulate_time[TIMESET_SIZE];
	int64_t		num_of_must_eat;
};

struct	s_resource
{
	pthread_mutex_t	*forks_array;
	pthread_mutex_t	logger_mutex;
	pthread_mutex_t	died_flag_mutex;
	bool			is_died_flag;
};

struct	s_philo
{
	pthread_t		thread_id;
	unsigned int	philo_id;
	unsigned int	primary_fork;
	unsigned int	secondary_fork;
	unsigned int	ate_count;
	uint64_t		last_meal_time;
	pthread_mutex_t	meal_mutex;
	t_table			*round;
};

struct	s_table
{
	t_philo		**philos;
	t_args		*sim_config;
	t_resource	*shared;
	uint64_t	sim_start_time;
	pthread_t	observer;
};

//parser
bool	parse_arguments(int argc, char **argv, t_args *parsed_args);

//philo_util
bool	philo_atoi(const char *origin_str, uint64_t *converted_num);
bool	philo_strlen(const char *str, size_t *len);
bool	is_valid_number(char c);
void	*philo_calloc(size_t mem_byte, size_t mem_size);

#endif
