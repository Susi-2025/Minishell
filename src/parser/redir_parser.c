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

int	redir_in_out(t_token *tokens, int token_count, int *i, t_cmd *cmds)
{
	if (tokens[*i].type == REDIR_IN)
	{
		(*i)++;
		if (*i < token_count && tokens[*i].type == WORD)
		{
			free(cmds->in_file);
			cmds->in_file = ft_strdup(tokens[*i].value);
			if (cmds->in_file == NULL)
				return (-1);
		}
	}
	else if (tokens[*i].type == REDIR_OUT)
	{
		(*i)++;
		if (*i < token_count && tokens[*i].type == WORD)
		{
			free(cmds->out_file);
			cmds->out_file = ft_strdup(tokens[*i].value);
			if (cmds->out_file == NULL)
				return (-1);
		}
	}
	return (0);
}

int	redir_special(t_token *tokens, int token_count, int *i, t_cmd *cmds)
{
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
		(*i)++;
		if (*i < token_count && tokens[*i].type == WORD)
		{
			free(cmds->here_doc);
			cmds->here_doc = ft_strdup(tokens[*i].value);
			if (cmds->here_doc == NULL)
				return (-1);
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
