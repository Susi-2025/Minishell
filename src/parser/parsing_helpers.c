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
