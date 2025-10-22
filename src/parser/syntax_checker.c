/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:15:35 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/22 13:31:21 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	check_initial_syntax(t_token *tokens, int token_count)
{
	if (token_count == 0)
		return (ERROR);
	if (token_count == 1 && tokens[0].type == TOKEN_EOF)
		return (SUCCESS);
	if (tokens[0].type == PIPE)
	{
		error_syntax(tokens[0].value);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	syntax_error_at_token(t_token *token)
{
	if (token->type == TOKEN_EOF)
		error_syntax("newline");
	else
		error_syntax(token->value);
	return (ERROR);
}

static int	is_redirection(t_token_type type)
{
	return (type == HERE_DOC || type == REDIR_IN
		|| type == REDIR_OUT || type == REDIR_APPEND);
}

static int	check_token_in_loop(t_token *tokens, int i)
{
	if (is_redirection(tokens[i].type))
	{
		if (tokens[i + 1].type != WORD)
			return (syntax_error_at_token(&tokens[i + 1]));
	}
	if (tokens[i].type == PIPE)
	{
		if (tokens[i + 1].type == PIPE || tokens[i + 1].type == TOKEN_EOF)
			return (syntax_error_at_token(&tokens[i + 1]));
	}
	return (SUCCESS);
}

int	syntax_checker(t_token *tokens, int t_count, t_cmd *cmds)
{
	int	i;

	i = 0;
	if (check_initial_syntax(tokens, t_count) == ERROR)
		return (ERROR);
	while (i < t_count && tokens[i].type != TOKEN_EOF)
	{
		if (check_token_in_loop(tokens, i) == ERROR)
			return (ERROR);
		if (tokens[i].type == HERE_DOC)
		{
			if (handle_heredoc(cmds, tokens[i + 1].value) == -1)
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
