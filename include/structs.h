/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:21:19 by cdohanic          #+#    #+#             */
/*   Updated: 2025/09/06 16:46:23 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_simple_cmd
{
	int     args_capacity;
	int     args_count;
	char    **args;
} t_simple_cmd;

typedef struct s_cmd
{
	int cmds_capacity;
	int cmds_count;
	t_simple_cmd **simple_cmds;
	char	*out_file;
	char	*in_file;
	char	*err_file;
	char	*here_doc;
	char	*file_append;
	char	**envp; //vietadd	
}	t_cmd;

typedef enum {
	WORD,
	DQUOTE_WORD,
	SQUOTE_WORD,
	VAR_WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HERE_DOC,
	ERROR_TOKEN,
	TOKEN_EOF,
}	t_token_type;

typedef struct {
	t_token_type	type;
	char			*value;
}	t_token;

#endif
