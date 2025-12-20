/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:11:32 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/20 18:30:53 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>

typedef struct	s_args
{
	uint64_t	num_of_philos;
	uint64_t	simulate_time[sizeof(t_times)];
	uint64_t	need_to_eat;
} t_args;

typedef enum	e_times
{
	die_ms;
	eat_ms;
	sleep_ms;
}	t_times ;

//parser
bool	parse_args(const int argc, const char **argv, t_args *parsed_args);

//philo_util
bool	philo_atoi(const char *origin_str, uint64_t *converted_num);
bool	philo_strlen(const char *str, size_t *len);
bool	is_valid_number(char c);
void	*philo_calloc(size_t mem_byte, size_t mem_size);

#endif
