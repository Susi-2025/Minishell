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
		if (l[*i + 1] == '<')
		{
			tokens[*count].type = HERE_DOC;
			tokens[*count].value = ft_strdup("<<");
			(*i) += 2;
		}
		else
		{
			tokens[*count].type = REDIR_IN;
			tokens[*count].value = ft_strdup("<");
			(*i)++;
		}
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
	}
}

static void	pipe_token(t_token *tokens, int *count, int *i)
{
	tokens[*count].type = PIPE;
	tokens[*count].value = ft_strdup("|");
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
		tokens[*count].value = malloc(len + 1);
		if (tokens[*count].value)
			ft_strlcpy(tokens[*count].value, l + start, len + 1);
		if (ft_strchr(tokens[*count].value, '$'))
			tokens[*count].type = VAR_WORD;
		else
			tokens[*count].type = WORD;
	}
}

static void	eof_token(t_token *tokens, int *count)
{
	tokens[*count].type = TOKEN_EOF;
	tokens[*count].value = NULL;
}

static void	quote_word_token(t_token *tokens, int *count, int *i, char *l)
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
	{
		tokens[*count].value = NULL;
		return ;
	}
	len = *i - start;
	if (len > 0)
	{
		if (c == '\'')
			tokens[*count].type = SQUOTE_WORD;
		else
			tokens[*count].type = DQUOTE_WORD;
		tokens[*count].value = malloc(len + 1);
		if (tokens[*count].value)
			ft_strlcpy(tokens[*count].value, l + start, len + 1);
	}
	(*i)++;
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

		if (l[i] == '"' || l[i] == '\'')
			quote_word_token(tokens, &count, &i, l);
		if (l[i] == '<' || l[i] == '>')
			redir_token(tokens, &i, &count, l);
		else if (l[i] == '|')
			pipe_token(tokens, &count, &i);
		else
			word_token(tokens, l, &count, &i);
		if (tokens[count].value == NULL && tokens[count].type != TOKEN_EOF)
			return (free_tokens(tokens, count), NULL);
		// if (tokens[count].type == VAR_WORD)
		// 	printf("VAR_WORD: %s\n", tokens[count].value);
		// else if (tokens[count].type == DQUOTE_WORD)
		// 	printf("DQUOTE_WORD: %s\n", tokens[count].value);	
		// else if (tokens[count].type == SQUOTE_WORD)
		// 	printf("SQUOTE_WORD: %s\n", tokens[count].value);	
		count++;
	}
	eof_token(tokens, &count);
	*token_count = count;
	return (tokens);
}

