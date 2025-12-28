# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/28 15:38:17 by sohyamaz          #+#    #+#              #
#    Updated: 2025/12/28 15:47:48 by sohyamaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Target declaration
NAME	= 	philo
SRCS	=	construct.c \
			destruct.c \
			main.c \
			observer.c \
			parser.c \
			philosophers.c \
			philo_util.c \
			print.c \
			simulation.c \
			threads_util.c \
			times.c \

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -pthread -g
OBJS	= $(SRCS:%.c=%.o)

#Declaration of rules

all	: $(NAME)

clean	:
	rm -rf $(OBJS)

fclean	: clean
	rm -rf $(NAME)

re	: fclean all

#Pony target declaration
.PHONY	: all re clean fclean

$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o	: %.c
	$(CC) $(CFLAGS) -c $< -o $@
