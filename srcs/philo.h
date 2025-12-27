/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:11:32 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/27 19:17:19 by sohyamaz         ###   ########.fr       */
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
bool	init_table(t_args *parsed_args, t_table **table);
bool	init_table_vars(t_table *table);
bool	init_philos(t_philo **philo, t_table *table);
bool	init_shared_mutex(t_resource *shared, uint64_t headcount);

//parser
bool	parse_arguments(int argc, char **argv, t_args *parsed_args);

//simulation
bool	start_simulation(t_table *table);
void	stop_simulation(t_table *table);

//observer
void	*monitor_routine(void *table_data);
bool	is_sim_finished(t_table *table);
void	set_is_died_flag(t_resource *shared, bool flag);
void	cremate_philo(t_resource *shared, t_philo *philo);
bool	is_philo_died(t_philo *philo);

//philosophers
void	*philo_routine(void *philo_data);

//print
void	print_log(t_resource *shared, t_philo *philo, \
		t_status status, bool is_died_notice);
void	print_status(t_philo *philo, char *msg);

//time_util
bool	get_time_in_millisec(uint64_t *millisec);
bool	wait_for_start_time(uint64_t sim_start_time);
void	take_short_sleep(uint64_t wait_ms);

//philo_util
bool	philo_atoi(const char *origin_str, uint64_t *converted_num);
bool	philo_strlen(const char *str, size_t *len);
bool	is_valid_number(char c);

//destructor
void	destruct_table(t_table *table);
void	destruct_shared_mutex(t_resource *shared);
void	destruct_philos(t_philo **philos, uint64_t headcount);
void	destruct_table_vars(t_table *table);
void	*philo_calloc(size_t mem_byte, size_t mem_size);

#endif
