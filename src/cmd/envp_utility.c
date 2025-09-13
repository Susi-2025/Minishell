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
static	int envp_err_free(char **temp_env, int pos);

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

// int	reduce_env(t_cmd *cmds, char *str, char **env)
int	reduce_env(t_cmd *cmds, char *str, char ***env)
{
	int i;
	int len;

	// if (!cmds || !str  || !env)
	if (!str || !env || !(*env))
		return (1);
	i = 0;
	len = ft_len_2d(*env);
	while ((*env)[i])
	{
		if (detect_var((*env)[i], str)== 0)
		{
			free((*env)[i]);
			while (i < len - 1)
			{
				(*env)[i] = (*env)[i + 1];
				i++;
			}
			(*env)[i] = NULL;
			return (0);
		}
		i++;
	}
	cmds->envp = *env;
	return (1);
}

static	int	detect_var(char *origin, char *expan)// need to modify to work like bash
{
	int	i;

	i = 0;
	while (origin[i] != '=')
		i++;
	if (ft_strncmp(&origin[i + 1], expan, ft_strlen(expan)) == 0)
		return (0);
	return (1);
}

int insert_env(t_cmd *cmds, char *str, char ***temp_env)
//int insert_env(char *str, char ***temp_env)
{
	int		len_envp;
	char	**new_env;
	int		i;

	len_envp = ft_len_2d(*temp_env);
	new_env = malloc(sizeof(char *) * (len_envp + 2));
	printf("Start to insert to env\n");
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
	printf("Before freeing env\n");
	ft_free_triptr(temp_env);
	printf("After freeing env\n");
	// ft_free_triptr(temp_env);
	*temp_env = new_env;
	cmds->envp = *temp_env;
	// exec_env(cmds);
	return (0);
}

static	int envp_err_free(char **temp_env, int pos)
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