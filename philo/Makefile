# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amejia <amejia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 14:12:43 by amejia            #+#    #+#              #
#    Updated: 2023/04/15 16:54:04 by amejia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = philo

NAME_DEBUG = philo_debug

SRCS = utils.c main.c kharon.c chronos.c ganymede.c philosopher.c \
prepros.c prepros2.c prepros3.c exit.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread -g

all: $(NAME)

bonus: $(NAME_BONUS)

clean: 
	rm -f $(OBJS) $(OBJS)

fclean: clean
	rm -f $(NAME) $(NAME_DEBUG) 
	
VS_debug: CFLAGS += -D DEBUG=1
VS_debug: $(NAME_DEBUG)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@ 

$(NAME_DEBUG): $(SRCS)
	$(CC) $(CFLAGS) -fdiagnostics-color=always -g $(SRCS) -o $@

re: fclean all

.PHONY: all clean fclean re VS_debug 
