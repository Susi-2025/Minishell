/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:44:35 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/22 14:44:36 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	cq_handle_outside(char *delimiter, int i, int *j_ptr,
		char *quote_char_ptr)
{
	if (delimiter[i] == '\'' || delimiter[i] == '\"')
	{
		*quote_char_ptr = delimiter[i];
		return (1);
	}
	else
	{
		delimiter[*j_ptr] = delimiter[i];
		(*j_ptr)++;
		return (0);
	}
}

static void	cq_handle_inside(char *delimiter, int i, int *j_ptr,
		char *quote_char_ptr)
{
	if (delimiter[i] == *quote_char_ptr)
		*quote_char_ptr = 0;
	else
	{
		delimiter[*j_ptr] = delimiter[i];
		(*j_ptr)++;
	}
}

static int	quotes_return(int quote_char, int quote_found)
{
	if (quote_char != 0)
		return (-1);
	if (quote_found)
		return (0);
	return (1);
}

int	contains_quotes(char *delimiter)
{
	int		i;
	int		j;
	char	quote_char;
	int		quote_found;

	i = 0;
	j = 0;
	quote_char = 0;
	quote_found = 0;
	while (delimiter[i])
	{
		if (quote_char == 0)
		{
			if (cq_handle_outside(delimiter, i, &j, &quote_char))
				quote_found = 1;
		}
		else
			cq_handle_inside(delimiter, i, &j, &quote_char);
		i++;
	}
	delimiter[j] = '\0';
	return (quotes_return(quote_char, quote_found));
}
