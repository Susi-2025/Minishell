/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:07:49 by cdohanic          #+#    #+#             */
/*   Updated: 2025/09/09 10:36:15 by vinguyen         ###   ########.fr       */
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
	int quote_flag;

	start = *i;
	quote_flag = 0; 
	while (l[*i] && (quote_flag || (!is_space(l[*i]) && !is_delimiter(l[*i]))))
	{
		if (l[*i] =='\"' || l[*i] =='\'')
			quote_flag = 1 - quote_flag;
		(*i)++;
	}	
	len = *i - start;
	if (len > 0)
	{
		token->value = malloc(len + 1);
		if (token->value == NULL)
			return (error_token(token));
		ft_strlcpy(token->value, l + start, len + 1);
		token->type = WORD;
	}
}
