/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:21:19 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/22 14:21:06 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum s_token_type
{
	WORD,
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

typedef struct s_vector
{
	int				args_capacity;
	int				args_count;
	t_token_type	*type;
	char			**args;
}	t_vector;

typedef struct s_simple_cmd
{
	int			args_capacity;
	int			args_count;
	char		**args;
	t_vector	*out_file;
	t_vector	*in_file;
}	t_simple_cmd;

typedef struct s_cmd
{
	int				cmds_capacity;
	int				cmds_count;
	int				err_code; //vietadd for handle error code
	t_simple_cmd	**simple_cmds; // cmd1(in, out) cmd2(in, out) cmd3(in,out)
	t_vector		*heredoc_files;
	int				heredoc_idx;
	char			*err_file;
	char			*file_append;
	char			**envp;
}	t_cmd;

#endif
