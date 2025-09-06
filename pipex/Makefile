# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/28 16:46:42 by cdohanic          #+#    #+#              #
#    Updated: 2025/07/03 13:51:21 by cdohanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
SRCS	=  ./utils/ft_split.c ./utils/ft_strjoin.c ./utils/str_utils.c ./utils/error_handling.c \
		./utils/init_and_close.c ./src/pipex.c ./src/cmd_parse.c ./src/process_exec.c 

OBJS	= $(SRCS:.c=.o)
CC		= gcc
CFLAGS	= -I./src -I./utils -Wall -Wextra -Werror

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
