/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:00:46 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/24 16:51:58 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	len_until_delim(char *word)
{
	int	i;

	if (!word)
		return (0);
	i = 0;
	while (word[i] && ft_isalnum(word[i]))
		i++;
	return (i);
}

int	find_dollar_pos(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
		return (i);
	return (-1);
}

char	*find_env_value(char *variable, char *env[], int var_len)
{
	int	i;

	if (!variable || !env || var_len <= 0)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		if (env[i] && ft_strncmp(variable, env[i], var_len) == 0
			&& env[i][var_len] == '=')
			return (ft_strdup(env[i] + var_len + 1));
		i++;
	}
	return (ft_strdup(""));
}
