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

// static int	count_token(char *l)
// {
// 	int	i;
// 	int	out;
// 	int	start;

// 	i = 0;
// 	start = 0;
// 	out = 0;
// 	while (l[i])
// 	{
// 		if (is_space(l[i]) == 0 && start == 0) //detect word
// 		{
// 			start = 1;
// 			out++;
// 		}
// 		else if (start == 1 && is_space(l[i])) //finish word
// 			start = 0;
// 		i++;
// 	}
// 	return (out);
// }

static	void	process_next_token(t_token *token, char *l, int *i)
{
	// if (l[*i] == '"' || l[*i] == '\'')
	// 	quote_word_token(token, i, l);
	if (l[*i] == '<' || l[*i] == '>')
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
	int		capacity;
	t_token	*tokens;

	count = 0;
	i = 0;
	capacity = 2;
	// tokens = malloc(sizeof(t_token) * 100);
	tokens = malloc(sizeof(t_token) * (capacity)); // token1, token2
	
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
		if (tokens[count].type == WORD)
		{
			printf("--WORD--\n");
			printf("TOKEN VALUE: %s\n", tokens[count].value);
		}
		count++;
		if (count == capacity)
		{
			tokens = ft_realloc(tokens, capacity * sizeof(t_token), capacity * 2 * sizeof(t_token));
			capacity *= 2;
		}
	}
	eof_token(tokens, &count);
	*token_count = count;
	return (tokens);
}

