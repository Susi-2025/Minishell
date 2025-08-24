/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:07:49 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/24 15:13:30 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	pipe_token(t_token *token, int *i)
{
	token->type = PIPE;
	token->value = ft_strdup("|");
	(*i)++;
}

void	eof_token(t_token *tokens, int *count)
{
	tokens[*count].type = TOKEN_EOF;
	tokens[*count].value = NULL;
}

void	word_token(t_token *token, char *l, int *i)
{
	int	start;
	int	len;

	start = *i;
	while (l[*i] && !is_space(l[*i]) && !is_delimiter(l[*i]))
		(*i)++;
	len = *i - start;
	if (len > 0)
	{
		token->value = malloc(len + 1);
		if (token->value == NULL)
			return (error_token(token));
		ft_strlcpy(token->value, l + start, len + 1);
		if (ft_strchr(token->value, '$'))
			token->type = VAR_WORD;
		else
			token->type = WORD;
	}
}

void	quote_word_token(t_token *token, int *i, char *l)
{
	int		start;
	int		len;
	char	c;

	c = l[*i];
	(*i)++;
	start = *i;
	while (l[*i] && l[*i] != c)
		(*i)++;
	if (l[*i] == '\0')
		return (error_token(token), (void)0);
	len = *i - start;
	token->value = malloc(len + 1);
	if (token->value == NULL)
		return (error_token(token), (void)0);
	ft_strlcpy(token->value, l + start, len + 1);
	if (c == '\'')
		token->type = SQUOTE_WORD;
	else
		token->type = DQUOTE_WORD;
	(*i)++;
}
