/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:27:52 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/17 19:27:55 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	cmd_init(t_cmd *cmds)
{
    cmds->cmds_capacity = 2;
    cmds->cmds_count = 0;
    cmds->in_file = NULL;
    cmds->out_file = NULL;
    cmds->err_file = NULL;
    cmds->here_doc = NULL;
    cmds->file_append = NULL;
	cmds->simple_cmds = malloc(sizeof(t_simple_cmd *) * cmds->cmds_capacity);
    if (!cmds->simple_cmds)
		return (-1);
	return (0);
}

static int	parse_word(const char *word, t_simple_cmd **current_cmd, t_cmd *cmds)
{
	void	*tmp;
	if (!*current_cmd)
	{
		if (cmds->cmds_count >= cmds->cmds_capacity)
		{
			cmds->cmds_capacity *= 2;
			tmp = realloc(cmds->simple_cmds, sizeof(t_simple_cmd) * cmds->cmds_capacity);
			if (!tmp)
				return (-1);
			cmds->simple_cmds = tmp;
		}
		*current_cmd = malloc(sizeof(t_simple_cmd));
		if (!*current_cmd)
			return (-1);
		(*current_cmd)->args_capacity = 4;
		(*current_cmd)->args_count = 0;
		(*current_cmd)->args = malloc(sizeof(char *) * (*current_cmd)->args_capacity);
		if (!(*current_cmd)->args)
			return (free(*current_cmd), -1);
		cmds->simple_cmds[cmds->cmds_count] = *current_cmd;
		cmds->cmds_count++;
	}
	if ((*current_cmd)->args_count >= (*current_cmd)->args_capacity - 1)
	{
		(*current_cmd)->args_capacity *= 2;
		tmp = realloc((*current_cmd)->args, sizeof(char *) * (*current_cmd)->args_capacity);
		if (!tmp)
			return (-1);
		(*current_cmd)->args = tmp;
	}
	(*current_cmd)->args[(*current_cmd)->args_count] = ft_strdup(word);
	if (!(*current_cmd)->args[(*current_cmd)->args_count])
		return (-1);
	(*current_cmd)->args_count++;
	(*current_cmd)->args[(*current_cmd)->args_count] = NULL;
	return (0);
}

static int	parse_redir(t_token *tokens, int token_count, int *i, t_cmd *cmds)
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
	else if (tokens[*i].type == REDIR_APPEND)
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
	return (0);
}

t_cmd	*parse_tokens(t_token *tokens, int token_count)
{
	t_cmd			*cmds;
	int				i;
	t_simple_cmd	*current_cmd;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	if (cmd_init(cmds) == -1)
		return (free(cmds), NULL);
	current_cmd = NULL;
	i = 0;
	while (i < token_count && tokens[i].type != TOKEN_EOF)
	{
		if (tokens[i].type == WORD)
		{
			if (parse_word(tokens[i].value, &current_cmd, cmds) == -1)
				return (free_cmd(cmds), NULL);
		}
		else if (tokens[i].type == REDIR_IN || tokens[i].type == REDIR_OUT || tokens[i].type == REDIR_APPEND)
		{
			if (parse_redir(tokens, token_count, &i, cmds) == -1)
				return (free_cmd(cmds), NULL);
		}
		else if (tokens[i].type == PIPE)
			current_cmd = NULL;
		i++;
	}
	return (cmds);
}

