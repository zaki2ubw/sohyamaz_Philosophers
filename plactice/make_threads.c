/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:49:43 by sohyamaz          #+#    #+#             */
/*   Updated: 2025/12/13 14:30:52 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <threads.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void	*notify_thread_id(void *unuse_arg);

int	main(int argc, char **argv)
{
	size_t	num_of_threads;
	size_t	count;
	size_t	joined;
	void	*thread_retval;
	pthread_t	*threads_id_array;

	if (argc != 2)
		return (1);
	num_of_threads = atoi(argv[1]);
	threads_id_array = (pthread_t *)calloc(num_of_threads, sizeof(pthread_t));
	if (threads_id_array == NULL)
		return (perror("malloc"), 1);
	count = 0;
	while (count < num_of_threads)
	{
		if (pthread_create(&threads_id_array[count], NULL, notify_thread_id, NULL) != 0)
			return (perror("pthread"), free(threads_id_array), 1);
		printf("current created thread_id is %lu\n", threads_id_array[count]);
		count++;
	}
	printf("created threads count is %zu\n", count);
	joined = 0;
	while (joined < num_of_threads)
	{
		pthread_join(threads_id_array[joined], &thread_retval);
		printf("this is retval of this joined thread %p\n", thread_retval);
		joined++;
	}
	printf("joined threads count is %zu\n", joined);
	free(threads_id_array);
	return (0);
}

void	*notify_thread_id(void *unuse_arg)
{
	(void)unuse_arg;
	printf("this thread is start as thread_id %lu\n", pthread_self());
	return ((void *)123);
}
