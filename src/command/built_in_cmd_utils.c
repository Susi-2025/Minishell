/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/23 13:41:27 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var(char **envp, char *str)
{
	int		i;
	char	*sub;

	if (!envp || !str)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
		{
			sub = ft_strchr_char(envp[i], '=');
			if (sub)
				return (sub + 1);
			break ;
		}
		i++;
	}
	return (NULL);
}

int	check_var_env(char **envp, char *str)
{
	int	i;
	int	len;

	if (!envp || !str)
		return (0);
	i = 0;
	len = ft_strlen(str);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
		{
			if (envp[i][len] == '=' || envp[i][len] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_is_numeric(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
