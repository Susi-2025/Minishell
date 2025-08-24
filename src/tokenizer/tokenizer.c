/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:18:07 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/24 15:14:09 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	error_token(t_token *token)
{
	token->type = ERROR_TOKEN;
	token->value = NULL;
}

static	void	process_next_token(t_token *token, char *l, int *i)
{
	if (l[*i] == '"' || l[*i] == '\'')
		quote_word_token(token, i, l);
	else if (l[*i] == '<' || l[*i] == '>')
		redir_token(token, i, l);
	else if (l[*i] == '|')
		pipe_token(token, i);
	else
		word_token(token, l, i);
	if (token->value == NULL && token->type != ERROR_TOKEN)
		error_token(token);
}

t_token	*tokenize(char *l, int *token_count)
{
	int		i;
	int		count;
	t_token	*tokens;

	count = 0;
	i = 0;
	tokens = malloc(sizeof(t_token) * 100);
	if (!tokens)
		return (NULL);
	while (l[i])
	{
		i = skip_whitespace(l, i);
		if (!l[i])
			break ;
		process_next_token(&tokens[count], l, &i);
		if (tokens[count].type == ERROR_TOKEN)
			return (free_tokens(tokens, count), NULL);
		count++;
	}
	eof_token(tokens, &count);
	*token_count = count;
	return (tokens);
}
