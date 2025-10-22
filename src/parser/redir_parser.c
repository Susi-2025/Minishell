/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:46:57 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/24 16:48:13 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_redir_vector(t_vector **vec_ptr)
{
	if (*vec_ptr != NULL)
		return (0);
	*vec_ptr = malloc(sizeof(t_vector));
	if (!*vec_ptr)
		return (-1);
	if (vector_setup(*vec_ptr) == VECTOR_ERROR)
	{
		free(*vec_ptr);
		*vec_ptr = NULL;
		return (-1);
	}
	return (0);
}

int	redir_in(t_token *tokens, int token_count, int *i, t_cmd *cmds)
{
	t_vector		*vec;
	t_simple_cmd	*cmd;
	int				token_type;

	cmd = cmds->simple_cmds[cmds->cmds_count - 1];
	token_type = tokens[*i].type;
	if (init_redir_vector(&cmd->redirections) == -1)
		return (-1);
	vec = cmd->redirections;
	(*i)++;
	if (*i < token_count && tokens[*i].type == WORD)
	{
		if (vector_push_back(vec, ft_strdup(tokens[*i].value)) == VECTOR_ERROR)
			return (-1);
		vec->type[vec->args_count - 1] = token_type;
	}
	return (0);
}

int	redir_out(t_token *tokens, int token_count, int *i, t_cmd *cmds)
{
	t_vector		*vec;
	t_simple_cmd	*cmd;
	int				token_type;

	cmd = cmds->simple_cmds[cmds->cmds_count - 1];
	token_type = tokens[*i].type;
	if (init_redir_vector(&cmd->redirections) == -1)
		return (-1);
	vec = cmd->redirections;
	(*i)++;
	if (*i < token_count && tokens[*i].type == WORD)
	{
		if (vector_push_back(vec, ft_strdup(tokens[*i].value)) == VECTOR_ERROR)
			return (-1);
		vec->type[vec->args_count - 1] = token_type;
	}
	return (0);
}

int	redir_here_doc(t_token *tokens, int token_count, int *i, t_cmd *cmds)
{
	t_simple_cmd	*cmd;
	t_vector		*vec;
	int				token_type;

	cmd = cmds->simple_cmds[cmds->cmds_count - 1];
	if (tokens[*i].type == HERE_DOC)
	{
		if (init_redir_vector(&cmd->redirections) == -1)
			return (-1);
		token_type = REDIR_IN;
		vec = cmd->redirections;
		(*i)++;
		if (*i < token_count && tokens[*i].type == WORD)
		{
			if (vector_push_back(cmd->redirections,
					ft_strdup(cmds->heredoc_files->args[cmds->heredoc_idx]))
				== VECTOR_ERROR)
				return (-1);
			cmds->heredoc_idx++;
			vec->type[vec->args_count - 1] = token_type;
		}
	}
	return (0);
}

int	parse_redir(t_token *tokens, int token_count, int *i, t_cmd *cmds)
{
	if (tokens[*i].type == REDIR_IN)
		return (redir_in(tokens, token_count, i, cmds));
	else if (tokens[*i].type == REDIR_OUT || tokens[*i].type == REDIR_APPEND)
		return (redir_out(tokens, token_count, i, cmds));
	else
		return (redir_here_doc(tokens, token_count, i, cmds));
	return (0);
}
