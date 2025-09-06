/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:09:44 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/24 15:09:49 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	handle_redir_in(t_token *token, int *i, char *l)
{
	if (l[*i + 1] == '<')
	{
		token->type = HERE_DOC;
		token->value = ft_strdup("<<");
		(*i) += 2;
	}
	else
	{
		token->type = REDIR_IN;
		token->value = ft_strdup("<");
		(*i)++;
	}
}

void	handle_redir_out(t_token *token, int *i, char *l)
{
	if (l[*i + 1] == '>')
	{
		token->type = REDIR_APPEND;
		token->value = ft_strdup(">>");
		(*i) += 2;
	}
	else
	{
		token->type = REDIR_OUT;
		token->value = ft_strdup(">");
		(*i)++;
	}
}

void	redir_token(t_token *token, int *i, char *l)
{
	if (l[*i] == '<')
		handle_redir_in(token, i, l);
	else if (l[*i] == '>')
		handle_redir_out(token, i, l);
}
