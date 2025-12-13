/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:14:15 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/13 20:50:16 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define LOOPS 1000000

void	*notify_threads(void *arg);

static int	shared_counter;

int	main(int argc, char **argv)
{
	size_t	num_of_thread;
	size_t	created;
	size_t	joined;
	void	*retval;
	pthread_t	*threads_array;

	if (argc != 2)
		return (1);
	num_of_thread = (size_t)atoi(argv[1]);
	threads_array = (pthread_t *)calloc(num_of_thread, sizeof(pthread_t));
	if (threads_array == NULL)
		return (perror("malloc"), 1);
	created = 0;
	shared_counter = 0;
	while (created < num_of_thread)
	{
		if (pthread_create(&threads_array[created], NULL, notify_threads, NULL) != 0)
		{
			fprintf(stderr, "error: pthread_create is failed");
			return (free(threads_array), 1);
		}
		created++;
	}
	printf("there is no mutex\n");
	joined = 0;
	while (joined < num_of_thread)
	{
		if (pthread_join(threads_array[joined], &retval) != 0)
		{
			fprintf(stderr, "error: pthread_join is failed");
			return (free(threads_array), 1);
		}
		joined++;
	}
	printf("expected count = %zu, actual count = %d\n", num_of_thread * (size_t)LOOPS, shared_counter);
	free(threads_array);
	return (0);
}

void	*notify_threads(void *arg)
{
	int	i;

	(void)arg;
	printf("this thread id is %lu\n", (unsigned long)pthread_self());
	i = 0;
	while (i < LOOPS)
	{
		shared_counter++;
		i++;
	}
	return ((void *)123);
}
