/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:35:40 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/22 17:35:41 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	handle_redirection(t_token *tokens, int token_count, int *i,
		t_cmd *cmds)
{
	if (is_redirect_token(tokens[*i].type))
	{
		if (tokens[*i + 1].type != TOKEN_EOF && tokens[*i + 1].type == WORD)
		{
			if (process_word(&tokens[*i + 1], NULL, cmds->envp,
					cmds->err_code) != SUCCESS)
				return (ERROR);
		}
		return (parse_redir(tokens, token_count, i, cmds));
	}
	return (0);
}

int	append_literal(char **result, char *line, int start, int end)
{
	char	*literal;
	char	*temp;

	if (start >= end)
		return (0);
	literal = ft_substr(line, start, end - start);
	if (!literal)
		return (free(*result), -1);
	temp = ft_strjoin(*result, literal);
	free(literal);
	if (!temp)
		return (free(*result), -1);
	free(*result);
	*result = temp;
	return (0);
}

int	append_variable(char **result, char *line, int *i, char *env[])
{
	char	*var_value;
	char	*temp;
	int		var_len;

	var_len = len_until_delim(line + *i);
	if (var_len == 0)
	{
		temp = ft_strjoin(*result, "$");
		free(*result);
		if (!temp)
			return (-1);
		*result = temp;
		return (0);
	}
	var_value = expand_single_var(line + *i, env);
	if (!var_value)
		return (free(*result), -1);
	temp = ft_strjoin(*result, var_value);
	free(var_value);
	if (!temp)
		return (free(*result), -1);
	free(*result);
	*result = temp;
	*i += var_len;
	return (0);
}
