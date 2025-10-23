/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:25:20 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/23 14:50:53 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

# include <fcntl.h> 
# include <errno.h>
# include <string.h>
# include <stddef.h>

# include "../libft/libft.h"

# include "tokenizer.h"
# include "structs.h"
# include "utils.h"
# include "parser.h"
# include "pipex.h"
# include "command.h"
# include "vector.h"

# define ERROR -1
# define MEM_ERROR -2
# define SUCCESS 0
# define DISCARD_TOKEN -3

t_cmd	*ft_prepare_command(char *line, char *env[], int error_code);
#endif
