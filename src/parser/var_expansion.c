/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:58:23 by cdohanic          #+#    #+#             */
/*   Updated: 2025/09/22 09:47:34 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_prefix(char **result, char *line, int dollar_pos)
{
	char	*prefix;
	char	*temp;

	if (dollar_pos <= 0)
		return (1);
	prefix = ft_substr(line, 0, dollar_pos);
	if (!prefix)
		return (0);
	temp = ft_strjoin(prefix, result[0]);
	free(prefix);
	if (!temp)
		return (0);
	free(result[0]);
	result[0] = temp;
	return (1);
}

static int	handle_suffix(char **result, char *variable, int var_len)
{
	char	*temp;
	int		last_idx;

	if (ft_strlen(variable) <= var_len)
		return (1);
	last_idx = 0;
	while (result[last_idx])
		last_idx++;
	if (last_idx == 0)
		return (1);
	last_idx--;
	temp = ft_strjoin(result[last_idx], variable + var_len);
	if (!temp)
		return (0);
	free(result[last_idx]);
	result[last_idx] = temp;
	return (1);
}

static char	**process_expansion(char *line, char *env[], int dollar_pos)
{
	char	*variable;
	char	**result;
	char	*env_value;
	int		var_len;

	variable = line + dollar_pos + 1;
	var_len = len_until_delim(variable);
	env_value = find_env_value(variable, env, var_len);
	if (!env_value)
		return (NULL);
	//MODIFY FT_SPLIT TO USE IS_SPACE INSTEAD OF ' '
	result = ft_split(env_value, ' ');
	free(env_value);
	if (!result)
		return (NULL);
	if (!handle_prefix(result, line, dollar_pos))
		return (free_split(result), NULL);
	if (!handle_suffix(result, variable, var_len))
		return (free_split(result), NULL);
	return (result);
}

char	**expand_var(char *line_value, char *env[])
{
	int		dollar_pos;

	if (!env || !line_value)
		return (NULL);
	dollar_pos = find_dollar_pos(line_value);
	if (dollar_pos == -1)
		return (NULL);
	return (process_expansion(line_value, env, dollar_pos));
}


char	*handle_var_exp(char *prefix, char *env_value, t_simple_cmd **current_cmd, char *var_name)
{
	char	**result;
	char	*last;
	int		i;

	result = ft_split(env_value, ' ');
	free(env_value);
	if (!result)
		return (NULL);
	result[0] = ft_strjoin_and_free(prefix, result[0]);
	if (result[0] == NULL)
		return (NULL);
	i = 0;
	if (current_cmd == NULL && result[i + 1] != NULL)
	{
		free_split(result);
		return (error_redir(var_name));
	}

	while (result[i + 1] != NULL)
	{
		if (parse_word(result[i], current_cmd) == -1)
			return (free_split(result), NULL);
		i++;
	}
	last = ft_strdup(result[i]);
	free_split(result);
	if (!last)
		return (NULL);
	return (last);
}

// int	handle_var_expansion(char *value, t_simple_cmd **current_cmd, char *env[])
// {
// 	char	**var_expansion;
// 	char	*last;
// 	int		i;

// 	var_expansion = expand_var(value, env);
// 	if (var_expansion == NULL)
// 		return (parse_word("", current_cmd));
// 	i = 0;
// 	while (var_expansion[i + 1] != NULL)
// 	{
// 		if (parse_word(var_expansion[i], current_cmd) == -1)
// 			return (free_split(var_expansion), NULL);
// 		i++;
// 	}
// 	last = ft_strdup(var_expansion[i]);
// 	free_split(var_expansion);
// 	if (!last)
// 		return (NULL);
// 	return (last);
// }
