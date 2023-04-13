# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amejia <amejia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 14:12:43 by amejia            #+#    #+#              #
#    Updated: 2023/04/13 15:29:11 by amejia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = philo

NAME_DEBUG = philo_debug

SRCS = utils.c main.c kharon.c chronos.c ganymede.c hermes.c philosopher.c \
prepros.c


OBJS = ${SRCS:.c=.o}

#CFLAGS = -Wall -Werror -Wextra

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
