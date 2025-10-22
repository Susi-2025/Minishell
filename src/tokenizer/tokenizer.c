/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:18:07 by cdohanic          #+#    #+#             */
/*   Updated: 2025/09/09 10:36:25 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_token(t_token *token)
{
	token->type = ERROR_TOKEN;
	token->value = NULL;
}

static void	process_next_token(t_token *token, char *l, int *i)
{
	if (l[*i] == '<' || l[*i] == '>')
		redir_token(token, i, l);
	else if (l[*i] == '|')
		pipe_token(token, i);
	else
		word_token(token, l, i);
	if (token->value == NULL && token->type != ERROR_TOKEN)
		error_token(token);
}

static int	check_and_resize_tokens(int *count, t_token **tokens, int *capacity)
{
	t_token	*new_tokens;

	if ((*tokens)[*count].type == ERROR_TOKEN)
	{
		free_tokens(*tokens, *count);
		return (ERROR);
	}
	(*count)++;
	if (*count == *capacity)
	{
		new_tokens = ft_realloc(*tokens, *capacity * sizeof(t_token), *capacity
				* 2 * sizeof(t_token));
		if (!new_tokens)
		{
			free_tokens(*tokens, *count);
			return (ERROR);
		}
		*tokens = new_tokens;
		*capacity *= 2;
	}
	return (SUCCESS);
}

t_token	*tokenize(char *l, int *token_count)
{
	int		i;
	int		count;
	int		capacity;
	t_token	*tokens;

	count = 0;
	i = 0;
	capacity = 2;
	tokens = malloc(sizeof(t_token) * (capacity));
	if (!tokens)
		return (NULL);
	while (l[i])
	{
		i = skip_whitespace(l, i);
		if (!l[i])
			break ;
		process_next_token(&tokens[count], l, &i);
		if (check_and_resize_tokens(&count, &tokens, &capacity) == ERROR)
			return (NULL);
	}
	eof_token(tokens, &count);
	*token_count = count;
	return (tokens);
}
