# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/16 12:30:39 by vinguyen          #+#    #+#              #
#    Updated: 2025/10/20 14:11:47 by vinguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude
LDLIBS = -lreadline

SRC_DIR = src
CMD_DIR = $(SRC_DIR)/command
EXE_DIR = $(SRC_DIR)/executer
HERE_DIR = $(SRC_DIR)/heredoc
PARS_DIR = $(SRC_DIR)/parser
TOKEN_DIR = $(SRC_DIR)/tokenizer
UTIL_DIR = $(SRC_DIR)/utils

MAIN_FILES = main.c
CMD_FILES = built_in_cmd.c cmd_cd.c cmd_echo.c cmd_export.c \
			envp_utils.c free_mem_utils.c init_envp.c start_built_in.c array_utils.c \
			built_in_cmd_utils.c print_utils.c str_envp_utils.c
EXE_FILES = error_handling.c init_and_close.c path_expansion.c pipex.c process_exec.c
HERE_FILES = heredoc_exec.c heredoc_pipe.c heredoc_utility.c
PARS_FILES = command_builder.c parser_main.c quote_parser.c redir_parser.c var_expansion.c 
TOKEN_FILES = cmd_tokens.c redir_tokens.c tokenizer.c
UTIL_FILES = err_utils.c char_utils.c cmd_print_utils.c ft_split.c memory_utils.c parser_utils.c str_copying.c \
			str_utils.c vector.c char_check_utils.c

SRC =	$(addprefix $(SRC_DIR)/, $(MAIN_FILES)) \
		$(addprefix $(CMD_DIR)/, $(CMD_FILES)) \
		$(addprefix $(EXE_DIR)/, $(EXE_FILES)) \
		$(addprefix $(HERE_DIR)/, $(HERE_FILES)) \
		$(addprefix $(PARS_DIR)/, $(PARS_FILES)) \
		$(addprefix $(TOKEN_DIR)/, $(TOKEN_FILES))\
		$(addprefix $(UTIL_DIR)/, $(UTIL_FILES))
		
OBJ_DIR = object

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

#SRC =	$(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
		
# OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# #OBJ	= $(SRC:%.c=$(OBJ_DIR)/%.o)

# $(OBJ_DIR)/%.o: src/%.c
# 	@mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) -c $< -o $@

OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#all: $(NAME)
all:$(LIBFT_LIB) $(NAME)

.SECONDARY: $(OBJ) $(LIBFT_OBJ)

#Build library
$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

#Build final executable
$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDLIBS) $(LIBFT_LIB)

#cleaning
clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
