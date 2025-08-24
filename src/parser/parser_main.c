/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:27:52 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/24 16:46:37 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	handle_word_tokens(t_token *token, t_simple_cmd **current_cmd,
	t_cmd *cmds, char *env[])
{
	char	*dquote;
	int		act;

	if (token->type == WORD)
		return (parse_word(token->value, current_cmd, cmds));
	if (token->type == VAR_WORD)
		return (handle_var_expansion(token->value, current_cmd, cmds, env));
	if (token->type == DQUOTE_WORD)
	{
		dquote = parse_dquote(token->value, env);
		act = parse_word(dquote, current_cmd, cmds);
		free(dquote);
		return (act);
	}
	if (token->type == SQUOTE_WORD)
		return (parse_word(token->value, current_cmd, cmds));
	return (0);
}

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

static int	process_word_and_redir(t_token *token, t_simple_cmd **current_cmd,
	t_cmd *cmds, char *env[])
{
	if (handle_word_tokens(token, current_cmd, cmds, env) == -1)
		return (-1);
	if (token->type == PIPE)
		*current_cmd = NULL;
	return (0);
}

static int	handle_redirection(t_token *tokens, int token_count,
	int *i, t_cmd *cmds)
{
	if (is_redirect_token(tokens[*i].type))
		return (parse_redir(tokens, token_count, i, cmds));
	return (0);
}

t_cmd	*parse_tokens(t_token *tokens, int token_count, char *env[])
{
	int				i;
	t_cmd			*cmds;
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
		if (process_word_and_redir(&tokens[i], &current_cmd, cmds, env) == -1)
			return (free_cmd(cmds), NULL);
		if (handle_redirection(tokens, token_count, &i, cmds) == -1)
			return (free_cmd(cmds), NULL);
		i++;
	}
	return (cmds);
}
