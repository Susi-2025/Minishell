# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/16 12:30:39 by vinguyen          #+#    #+#              #
#    Updated: 2025/08/16 12:30:48 by vinguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC_DIR = .
OBJ_DIR = ./object

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRC =	0_minishell.c \
		
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

all:$(LIBFT_LIB) $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.SECONDARY: $(OBJ) $(LIBFT_OBJ)

#Build library
$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

#Build final executable
$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME)

#cleaning
clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
