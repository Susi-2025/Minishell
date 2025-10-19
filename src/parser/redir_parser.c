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

// static int vector_init(t_vector *vec)
// {
// 	vec = malloc(sizeof(t_vector));
// 	if (!vec)
// 		return (-1);
// 	vec->args_capacity = 4;
// 	vec->args_count = 0;
// 	vec->args = malloc(sizeof(char *) * vec->args_capacity);
// 	if (!vec->args)
// 		return (free(vec), -1);
// 	return (0);
// }

int	redir_in_out(t_token *tokens, int token_count, int *i, t_cmd *cmds)
{
	int	idx;

	idx = cmds->cmds_count - 1;
	if (tokens[*i].type == REDIR_IN)
	{
		if (cmds->simple_cmds[idx]->in_file == NULL)
		{
			cmds->simple_cmds[idx]->in_file = malloc(sizeof(t_vector));
			if (!cmds->simple_cmds[idx]->in_file)
				return (-1);
			if (vector_setup(cmds->simple_cmds[idx]->in_file) == VECTOR_ERROR)
				return (-1);
		}
		(*i)++;
		if (*i < token_count && tokens[*i].type == WORD)
		{
			if (vector_push_back(cmds->simple_cmds[idx]->in_file, ft_strdup(tokens[*i].value)) == VECTOR_ERROR)
				return (-1);
		}
	}
	else if (tokens[*i].type == REDIR_OUT)
	{
		if (cmds->simple_cmds[idx]->out_file == NULL)
		{
			cmds->simple_cmds[idx]->out_file = malloc(sizeof(t_vector));
			if (!cmds->simple_cmds[idx]->out_file)
				return (-1);
			if (vector_setup(cmds->simple_cmds[idx]->out_file) == VECTOR_ERROR)
				return (-1);
		}
		(*i)++;
		if (*i < token_count && tokens[*i].type == WORD)
		{
			if (vector_push_back(cmds->simple_cmds[idx]->out_file, ft_strdup(tokens[*i].value)) == VECTOR_ERROR)
				return (-1);
		}
	}
	return (0);
}

int	redir_special(t_token *tokens, int token_count, int *i, t_cmd *cmds)
{
	int	idx;

	idx = cmds->cmds_count - 1;
	if (tokens[*i].type == REDIR_APPEND)
	{
		(*i)++;
		if (*i < token_count && tokens[*i].type == WORD)
		{
			free(cmds->file_append);
			cmds->file_append = ft_strdup(tokens[*i].value);
			if (cmds->file_append == NULL)
				return (-1);
		}
	}
	else if (tokens[*i].type == HERE_DOC)
	{
		if (cmds->simple_cmds[idx]->in_file == NULL)
		{
			cmds->simple_cmds[idx]->in_file = malloc(sizeof(t_vector));
			if (!cmds->simple_cmds[idx]->in_file)
				return (-1);
			if (vector_setup(cmds->simple_cmds[idx]->in_file) == VECTOR_ERROR)
				return (-1);
		}
		(*i)++;
		if (*i < token_count && tokens[*i].type == WORD)
		{
			if (vector_push_back(cmds->simple_cmds[idx]->in_file, ft_strdup(cmds->heredoc_files->args[cmds->heredoc_idx])) == VECTOR_ERROR)
				return (-1);
			cmds->heredoc_idx++;
		}
	}
	return (0);
}

int	parse_redir(t_token *tokens, int token_count, int *i, t_cmd *cmds)
{
	if (tokens[*i].type == REDIR_IN || tokens[*i].type == REDIR_OUT)
		return (redir_in_out(tokens, token_count, i, cmds));
	else
		return (redir_special(tokens, token_count, i, cmds));
}

int	is_redirect_token(int type)
{
	if (type == REDIR_IN)
		return (1);
	if (type == REDIR_OUT)
		return (1);
	if (type == REDIR_APPEND)
		return (1);
	if (type == HERE_DOC)
		return (1);
	return (0);
}
