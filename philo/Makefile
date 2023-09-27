# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/17 13:25:08 by casomarr          #+#    #+#              #
#    Updated: 2023/09/08 17:31:56 by casomarr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

NAME_SRC = philo

HEADER = src/philosophers.h

SRC = src/main.c \
	src/init.c \
	src/utils.c \
	src/eat.c \
	src/eat2.c \
	src/threads.c \
	src/print.c \
	src/stop.c \

SRC_OBJS = $(SRC:.c=.o)

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g3

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME_SRC): $(SRC_OBJS)
	@toilet PHILOSOPHERS -F border -f wideterm
	$(CC) $(CFLAGS) -o $(NAME_SRC) $(SRC_OBJS)

all: $(NAME_SRC)
	clear
	@toilet COMPILED -F border -f wideterm

clean:
	$(RM) $(SRC_OBJS)
	clear
	@toilet CLEAN -F border -f wideterm

fclean: clean
	$(RM) $(NAME_SRC)
	clear
	@toilet FCLEAN -F border -f wideterm

re: fclean all

.PHONY: all clean fclean re