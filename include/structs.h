/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:21:19 by cdohanic          #+#    #+#             */
/*   Updated: 2025/09/21 11:48:25 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_simple_cmd
{
	int		args_capacity;
	int		args_count;
	char	**args; 
}	t_simple_cmd;

typedef struct s_vector
{
	int 	args_capacity;
	int		args_count;
	char	**args;
}	t_vector;

typedef struct s_cmd
{
	int				cmds_capacity;
	int				cmds_count;
	int				err_code; //vietadd for handle error code
	t_simple_cmd	**simple_cmds;
	t_vector		*out_file;
	char			*in_file;
	char			*err_file;
	char			*here_doc;
	char			*here_doc_cont;
	char			*file_append;
	char			**envp; //vietadd	
}	t_cmd;

typedef enum s_token_type
{
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

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;
#endif
