/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1y_env_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/19 16:02:21 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_copy_str(char *origin, char *key, char *value);

int	update_env(t_shell *shell, char *key, char *value)
{
	int	i;
	char	*new_str;
	
	if (!shell || !key || !value)
		return (1);
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key, ft_strlen(key)) == 0)
		{
			new_str = malloc(sizeof(char) * (ft_strlen(key) + ft_strlen(value) + 2));
			if (!new_str)
				return (1); 
			ft_copy_str(new_str, key, value);
			free(shell->envp[i]);
			shell->envp[i] = new_str;
			return (0);
		}
		i++;
	}
	printf("Update fail\n");
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

int	reduce_env(t_shell *shell, char *str)
{
	int i;
	int len;

	if (!shell || !str)
		return (1);
	i = 0;
	len = ft_len_2d(shell->envp);
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], str, ft_strlen(str)) == 0
	&& shell->envp[i][ft_strlen(str)] == '=')
		{
			// printf("Variable is detect: %s\n", str);
			free(shell->envp[i]);
			while (i < len - 1)
			{
				// printf("Copy str: %d\n", i);
				shell->envp[i] = shell->envp[i + 1];
				i++;
			}
			shell->envp[i] = NULL;
			// i = 0;
			// printf("Check envp again\n");
			// while (shell->envp[i])
			// {
			// 	printf("String at %i pos is: %s\n", i, shell->envp[i]);
			// 	i++;
			// }
			return (0);
		}
		i++;
	}
	return (1);
}