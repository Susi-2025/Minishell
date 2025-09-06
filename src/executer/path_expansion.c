/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:32:23 by cdohanic          #+#    #+#             */
/*   Updated: 2025/07/03 13:58:09 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*correct_path(char *cmd, char *env[])
{
	int		i;
	char	**paths;
	char	*try_path;

	//SEPARATE TOMMOROW
	char	*temp;


	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	temp = ft_strjoin("/", cmd);
	if (!temp)
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (free(temp), NULL);
	i = -1;
	while (paths[++i])
	{
		try_path = ft_strjoin(paths[i], temp);
		if (access(try_path, F_OK) == 0)
		{
			free(temp);
			free_strings(paths);
			return (try_path);
		}
		free(try_path);
	}
	free(temp);
	free_strings(paths);
	return (NULL);
}

// char	**parse_cmd(char *argv, char *env[])
// {
// 	char	*path;
// 	char	**cmd;
// 	char	*temp;

// 	cmd = ft_split(argv, ' ');
// 	temp = ft_strjoin("/", cmd[0]);
// 	free(cmd[0]);
// 	cmd[0] = temp;
// 	path = correct_path(env, cmd[0]);
// 	if (path == NULL)
// 	{
// 		free_strings(cmd);
// 		return (NULL);
// 	}
// 	free(cmd[0]);
// 	cmd[0] = path;
// 	return (cmd);
// }
