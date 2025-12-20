/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:22:25 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/20 18:59:27 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_atoi(const char *origin_str, uint64_t *converted_num)
{
	uint64_t	tmp_for_calc;
	size_t		origin_len;
	size_t		i;

	if (origin_str == NULL || converted_num == NULL || origin_str[0] == 0)
		return (0);
	origin_len = 0;
	tmp_for_calc = 0;
	if (philo_strlen(origin_str, &origin_len) == 0)
		return (0);
	i = 0;
	while (i < origin_len)
	{
		if (is_valid_number(origin_str[i]) == 0)
			return (0);
		tmp_for_calc = tmp_for_calc * 10 + (origin_str[i] - '0');
		i++;
	}
	*converted_num = tmp_for_calc;
	return (1);
}

bool	philo_strlen(const char *str, size_t *len)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	*len = i;
	return (1);
}

bool	is_valid_number(char c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

void	*philo_calloc(size_t mem_byte, size_t mem_size)
{
	unsigned char	*allocated_buf;
	size_t			allocate_size;
	size_t			i;

	if (mem_byte == 0 || mem_size == 0)
		return (NULL);
	if (mem_size != 0 && mem_byte != 0 && mem_byte > SIZE_MAX / mem_size)
		return (NULL);
	allocate_size = mem_byte * mem_size;
	allocated_buf = (unsigned char *)malloc(allocate_size);
	if (allocated_buf == NULL)
		return (NULL);
	i = 0;
	while (i < allocate_size)
	{
		allocated_buf[i] = 0;
		i++;
	}
	return (allocated_buf);
}
