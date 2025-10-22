/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:07:17 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/22 13:43:39 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_exit_code(char **result, int *i, int exit_code)
{
	char	*exit_str;

	(*i)++;
	exit_str = ft_itoa(exit_code);
	if (!exit_str)
		return (-1);
	*result = ft_strjoin_and_free(*result, exit_str);
	if (!*result)
		return (-1);
	return (0);
}

static int	process_heredoc_expansion_loop(char **result, char *line,
		char *env[], int exit_code)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (append_literal(result, line, start, i) == -1)
				return (-1);
			i++;
			if (line[i] == '?')
			{
				if (append_exit_code(result, &i, exit_code) == -1)
					return (-1);
			}
			else if (append_variable(result, line, &i, env) == -1)
				return (-1);
			start = i;
		}
		else
			i++;
	}
	return (append_literal(result, line, start, i));
}

char	*parse_heredoc(char *line, char *env[], int exit_code)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
	{
		free(line);
		return (NULL);
	}
	if (process_heredoc_expansion_loop(&result, line, env, exit_code) == -1)
	{
		free(result);
		free(line);
		return (NULL);
	}
	free(line);
	return (result);
}
