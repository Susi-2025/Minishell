/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:53:17 by cdohanic          #+#    #+#             */
/*   Updated: 2025/09/09 10:35:53 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_single_var(char *var, char *env[])
{
	int	i;
	int	len;

	i = 0;
	len = len_until_delim(var);
	while (env[i])
	{
		if (ft_strncmp(var, env[i], len) == 0 && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

int	append_literal(char **result, char *line, int start, int end)
{
	char	*literal;
	char	*temp;

	if (start >= end)
		return (0);
	literal = ft_substr(line, start, end - start);
	if (!literal)
		return (free(*result), -1);
	temp = ft_strjoin(*result, literal);
	free(literal);
	if (!temp)
		return (free(*result), -1);
	free(*result);
	*result = temp;
	return (0);
}

int	append_variable(char **result, char *line, int *i, char *env[])
{
	char	*var_value;
	char	*temp;
	int		var_len;

	var_len = len_until_delim(line + *i);
	if (var_len == 0)
	{
		temp = ft_strjoin(*result, "$");
		free(*result);
		if (!temp)
			return (-1);
		*result = temp;
		return (0);
	}
	var_value = expand_single_var(line + *i, env);
	if (!var_value)
		return (free(*result), -1);
	temp = ft_strjoin(*result, var_value);
	free(var_value);
	if (!temp)
		return (free(*result), -1);
	free(*result);
	*result = temp;
	*i += var_len;
	return (0);
}

char	*parse_dquote(char *line, int *j, char *env[], int exit_code)
{
	char	*result;
	int		i;
	int		start;

	i = 0;
	start = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (line[i] && line[i] != '\"')
	{
		if (line[i] == '$')
		{
			if (append_literal(&result, line, start, i) == -1)
				return (NULL);
			i++;
			if (line[i] == '?')
			{
				result = ft_strjoin_and_free(result, ft_itoa(exit_code));
				if (!result)
					return (NULL);
				i++;
			}
			else if (append_variable(&result, line, &i, env) == -1)
				return (NULL);
			start = i;
		}
		else
			i++;
	}
	if (line[i] == '\0')
	{
		free(result);
		return (NULL);
	}
	if (append_literal(&result, line, start, i) == -1)
		return (NULL);
	(*j) += i;
	return (result);
}
