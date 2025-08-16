# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 16:29:22 by vinguyen          #+#    #+#              #
#    Updated: 2025/07/31 13:05:09 by vinguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
OBJ_DIR = obj

SRCS = ft_bzero.c ft_calloc.c ft_free_triptr.c \
	   ft_gnl.c \
	   ft_isalnum.c ft_isascii.c ft_isalpha.c ft_isdigit.c ft_isprint.c \
       ft_atoi.c ft_itoa.c \
	   ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	   ft_putchar_fd.c ft_putendl_fd.c \
       ft_putnbr_fd.c ft_putstr_fd.c \
	   ft_split.c \
	   ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
       ft_strmapi.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
       ft_strrchr.c ft_strtrim.c ft_substr.c \
	   ft_tolower.c ft_toupper.c \
	   ft_strlcpy.c

OBJ = $(SRCS:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.SECONDARY: $(OBJ)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

clean:
	$(RM) -rf $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
