/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:11:32 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/28 14:38:09 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define NO_SIM_LIMIT 0
# define MUST_WAIT 50

typedef enum e_timeset		t_timeset;
typedef enum e_status		t_status;
typedef struct s_args		t_args;
typedef struct s_philo		t_philo;
typedef struct s_resource	t_resource;
typedef struct s_table		t_table;

enum	e_timeset
{
	DIE_MS = 0,
	EAT_MS = 1,
	SLEEP_MS = 2,
	TIMESET_SIZE = 3
};

enum	e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	TAKE_FORK_1 = 4,
	TAKE_FORK_2 = 5,
	STATUS_SIZE = 6
};

struct	s_args
{
	uint64_t	headcount;
	uint64_t	simulate_time[TIMESET_SIZE];
	uint64_t	num_of_must_eat;
};

struct	s_resource
{
	pthread_mutex_t	*forks_array;
	pthread_mutex_t	logger_mutex;
	pthread_mutex_t	died_flag_mutex;
	uint64_t		forks_init_count;
	bool			is_logger_init;
	bool			is_died_mutex_init;
	bool			is_died_flag;
};

struct	s_philo
{
	pthread_t		thread_id;
	unsigned int	philo_id;
	unsigned int	primary_fork;
	unsigned int	secondary_fork;
	uint64_t		ate_count;
	uint64_t		last_meal_time;
	pthread_mutex_t	meal_mutex;
	bool			is_meal_init;
	t_table			*round;
};

struct	s_table
{
	t_philo		**philos;
	t_args		*config;
	t_resource	*shared;
	uint64_t	sim_start_time;
	pthread_t	observer;
};

//constructor
bool	construct_table(t_args *parsed_args, t_table **table);

//parser
bool	parse_arguments(int argc, char **argv, t_args *parsed_args);

//simulation
bool	start_simulation(t_table *table);
void	stop_simulation(t_table *table);

//routines
void	*philo_routine(void *philo_data);
void	*monitor_routine(void *table_data);

//print
void	print_log(t_resource *shared, t_philo *philo, \
		t_status status, bool is_died_notice);

//time_util
bool	get_time_in_millisec(uint64_t *millisec);
bool	set_sim_start_time(uint64_t	*sim_start_time, const uint64_t headcount);
bool	wait_for_start_time(const uint64_t sim_start_time);
void	take_short_wait(const uint64_t wait_ms);
void	wait_until_finish_task(t_table *table, const uint64_t task_term);

//philo_util
bool	philo_atoi(const char *origin_str, uint64_t *converted_num);
void	*philo_calloc(size_t mem_byte, size_t mem_size);

//threads_util
void	set_is_died_flag(t_resource *shared, bool flag);
bool	is_anyone_died(t_table *table);
void	*philo_must_die(t_philo *philo);

//destructor
void	destruct_table(t_table *table);

#endif
