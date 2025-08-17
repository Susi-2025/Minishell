/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:18:07 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/17 19:18:11 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	redir_token(t_token *tokens, int *i, int *count, char *l)
{
	if (l[*i] == '<')
	{
		tokens[*count].type = REDIR_IN;
		tokens[*count].value = ft_strdup("<");
		(*count)++;
		(*i)++;
	}
	else if (l[*i] == '>')
	{
		if (l[*i + 1] == '>')
		{
			tokens[*count].type = REDIR_APPEND;
			tokens[*count].value = ft_strdup(">>");
			(*i) += 2;
		}
		else
		{
			tokens[*count].type = REDIR_OUT;
			tokens[*count].value = ft_strdup(">");
			(*i)++;
		}
		(*count)++;
	}
}

static void	pipe_token(t_token *tokens, int *count, int *i)
{
	tokens[*count].type = PIPE;
	tokens[*count].value = ft_strdup("|");
	(*count)++;
	(*i)++;
}

static void	word_token(t_token *tokens, char *l, int *count, int *i)
{
	int	start;
	int	len;

	start = *i;
	while (l[*i] && !is_space(l[*i]) && !is_delimiter(l[*i]))
		(*i)++;
	len = *i - start;
	if (len > 0)
	{
		tokens[*count].type = WORD;
		tokens[*count].value = malloc(len + 1);
		if (tokens[*count].value)
		{
			ft_strlcpy(tokens[*count].value, l + start, len + 1);
		}
		(*count)++;
	}
}

static void	eof_token(t_token *tokens, int *count)
{
	tokens[*count].type = TOKEN_EOF;
	tokens[*count].value = NULL;
	(*count)++;
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
		while (l[i] && is_space(l[i]))
			i++;
		if (!l[i])
			break ;
		if (l[i] == '<' || l[i] == '>')
			redir_token(tokens, &i, &count, l);
		else if (l[i] == '|')
			pipe_token(tokens, &count, &i);
		else
			word_token(tokens, l, &count, &i);
	}
	eof_token(tokens, &count);
	*token_count = count;
	return (tokens);
}

