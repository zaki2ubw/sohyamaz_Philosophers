/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_outloop_mutex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:51:22 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/14 16:08:51 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define LOOPS 1000000

void	*notify_threads(void *arg);

static int	shared_counter;
static pthread_mutex_t	atomic_key;

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
	if (pthread_mutex_init(&atomic_key, NULL) != 0)
	{
		fprintf(stderr, "error: mutex_init is failed");
		return (free(threads_array), 1);
	}
	printf("there is a mutex\n");
	while (created < num_of_thread)
	{
		if (pthread_create(&threads_array[created], NULL, notify_threads, NULL) != 0)
		{
			fprintf(stderr, "error: pthread_create is failed");
			return (free(threads_array), 1);
		}
		created++;
	}
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
	if (pthread_mutex_destroy(&atomic_key) != 0)
	{
		fprintf(stderr, "error: mutex_init is failed");
		return (free(threads_array), 1);
	}
	free(threads_array);
	return (0);
}

void	*notify_threads(void *arg)
{
	int	i;

	(void)arg;
	i = 0;
	if (pthread_mutex_lock(&atomic_key) != 0)
	{
		fprintf(stderr, "error: mutex_lock is failed");
		return ((void *)321);
	}
	while (i < LOOPS)
	{
		shared_counter++;
		i++;
	}
	printf("Thread id %lu counted %d times.\n", (unsigned long)pthread_self(), i);
	if (pthread_mutex_unlock(&atomic_key) != 0)
	{
		fprintf(stderr, "error: mutex_unlock is failed");
		return ((void *)321);
	}
	return ((void *)123);
}
