/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:25:20 by cdohanic          #+#    #+#             */
/*   Updated: 2025/09/22 15:33:53 by vinguyen         ###   ########.fr       */
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
# include "heredoc.h"
# include "vector.h"

# define ERROR -1
# define SUCCESS 0
#endif
