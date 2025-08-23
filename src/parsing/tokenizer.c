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

static void	error_token(t_token *token)
{
	token->type = ERROR_TOKEN;
	token->value = NULL;
}

static void	handle_redir_in(t_token *token, int *i, char *l)
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

static void	handle_redir_out(t_token *token, int *i, char *l)
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

static void	redir_token(t_token *token, int *i, char *l)
{
	if (l[*i] == '<')
		handle_redir_in(token, i, l);
	else if (l[*i] == '>')
		handle_redir_out(token, i, l);
}

static void	pipe_token(t_token *token, int *i)
{
	token->type = PIPE;
	token->value = ft_strdup("|");
	(*i)++;
}

static void	word_token(t_token *token, char *l, int *i)
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

static void	eof_token(t_token *tokens, int *count)
{
	tokens[*count].type = TOKEN_EOF;
	tokens[*count].value = NULL;
}

static void	quote_word_token(t_token *token, int *i, char *l)
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

static int	skip_whitespace(char *l, int i)
{
	while (l[i] && is_space(l[i]))
		i++;
	return (i);
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
