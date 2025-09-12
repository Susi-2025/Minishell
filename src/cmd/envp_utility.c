/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1y_env_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/08 11:36:44 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_copy_str(char *origin, char *key, char *value);
static	int	detect_var(char *origin, char *expan);

int	update_env(t_cmd *cmds, char *key, char *value)
{
	int	i;
	char	*new_str;
	
	if (!cmds || !key || !value)
		return (1);
	i = 0;
	while (cmds->envp[i])
	{
		if (ft_strncmp(cmds->envp[i], key, ft_strlen(key)) == 0 &&
			cmds->envp[i][ft_strlen(key)] == '=')
		{
			// printf("Find the string: %s\n", cmds->envp[i]);
			new_str = malloc(sizeof(char) * (ft_strlen(key) + ft_strlen(value) + 2));
			if (!new_str)
				return (1); 
			ft_copy_str(new_str, key, value);
			// printf("Copy new string: %s\n", new_str);
			free(cmds->envp[i]);
			cmds->envp[i] = new_str;
			return (0);
		}
		i++;
	}
	// printf("Uppdate fail: key '%s' not found\n", key);
	return (1);
}

static	void	ft_copy_str(char *origin, char *key, char *value)
{
	int	j;
	int	k;
	
	j = 0;
	while (key[j])
	{
		origin[j] = key[j];
		j++;
	}
	origin[j++] = '=';
	k = 0;
	while (value[k])
		origin[j++] = value[k++];
	origin[j] = '\0';
}

int	reduce_env(t_cmd *cmds, char *str)
{
	int i;
	int len;

	if (!cmds || !str)
		return (1);
	i = 0;
	len = ft_len_2d(cmds->envp);
	while (cmds->envp[i])
	{
		if (detect_var(cmds->envp[i], str)== 0)
		{
			free(cmds->envp[i]);
			while (i < len - 1)
			{
				cmds->envp[i] = cmds->envp[i + 1];
				i++;
			}
			cmds->envp[i] = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

static	int	detect_var(char *origin, char *expan)
{
	int	i;

	i = 0;
	while (origin[i] != '=')
		i++;
	if (ft_strncmp(&origin[i + 1], expan, ft_strlen(expan)) == 0)
		return (0);
	return (1);
}