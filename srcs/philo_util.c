/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:22:25 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/20 17:22:58 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_atoi(const char *origin_str, uint64_t *converted_num)
{
	uint64_t	tmp_for_calc;
	size_t		origin_len;
	size_t		i;

	if (origin_str == NULL || converted == NULL || origin_str[0] == 0)
		return (0);
	origin_len = 0;
	tmp_for_calc = 0;
	if (philo_strlen(origin_str, &origin_len) == 0)
		return (0);
	while (i < origin_len)
	{
		if (is_valid_number(origin_str[i]) == 0)
			return (0);
		tmp_for_calc = tmp_for_calc + (origin_str[i] - '0');
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
