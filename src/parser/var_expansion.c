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

char	*check_for_redir(char **result, char *var_name)
{
	free_split(result);
	return (error_redir(var_name));
}

char	*return_free_split(char **result)
{
	free_split(result);
	return (NULL);
}

char	*handle_var_exp(char *prefix, char *env_value,
	t_simple_cmd **current_cmd, char *var_name)
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
		return (return_free_split(result));
	i = 0;
	if (current_cmd == NULL && result[i + 1] != NULL)
		return (check_for_redir(result, var_name));
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
