/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/16 17:09:26 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	void	ft_copy_str(char *origin, char *key, char *value);
static	int	detect_var(char *origin, char *expan);
static	int	envp_err_free(char **temp_env, int pos);
// static	char	*create_new_str(char *key, char *value);

int	update_env(t_cmd *cmds, char *key, char *value)
{
	int		i;
	char	*new_str;
	int		len_key;

	if (!cmds || !key)
		return (1);
	i = 0;
	len_key = ft_strlen(key);
	while (cmds->envp[i])
	{
		if (ft_strncmp(cmds->envp[i], key, len_key) == 0
			&& (cmds->envp[i][len_key] == '='
			|| cmds->envp[i][len_key] == '\0'))
		{
			new_str = create_new_str(key, value);
			if (!new_str)
				return (1);
			free(cmds->envp[i]);
			cmds->envp[i] = new_str;
			return (0);
		}
		i++;
	}
	return (1);
}

int	reduce_env(t_cmd *cmds, char *str, char ***temp_env)
{
	int	i;
	int	len;

	if (!str || !temp_env || !(*temp_env))
		return (1);
	i = 0;
	len = ft_len_2d(*temp_env);
	while (i < len && (*temp_env)[i])
	{
		if (detect_var((*temp_env)[i], str) == 0)
		{
			free((*temp_env)[i]);
			while (i < len - 1)
			{
				(*temp_env)[i] = (*temp_env)[i + 1];
				i++;
			}
			(*temp_env)[i] = NULL;
			return (0);
		}
		i++;
	}
	cmds->envp = *temp_env;
	return (0);
}

static	int	detect_var(char *origin, char *expan)
{
	int	len;

	if (!origin || !expan)
		return (1);
	len = ft_strlen(expan);
	if (ft_strncmp(origin, expan, len) == 0 && origin[len] == '=')
		return (0);
	return (1);
}

int	insert_env(t_cmd *cmds, char *str, char ***temp_env)
{
	int		len_envp;
	char	**new_env;
	int		i;

	len_envp = ft_len_2d(*temp_env);
	new_env = malloc(sizeof(char *) * (len_envp + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < len_envp)
	{
		new_env[i] = ft_strdup((*temp_env)[i]);
		if (!new_env[i])
			return (envp_err_free(new_env, i));
		i++;
	}
	new_env[i] = ft_strdup(str);
	if (!new_env[i])
		return (envp_err_free(new_env, i));
	new_env[i + 1] = NULL;
	ft_free_triptr(temp_env);
	*temp_env = new_env;
	cmds->envp = *temp_env;
	printf("Already insert\n");
	return (0);
}

static	int	envp_err_free(char **temp_env, int pos)
{
	int	i;

	i = 0;
	while (temp_env[i] && i < pos)
	{
		free(temp_env[i]);
		i++;
	}
	free(temp_env);
	return (1);
}
