/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:32:23 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/25 17:05:46 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**make_path(char *env[]);
static char	*free_for_path(char *temp, char **paths, char *path);
static int	is_directory(char *path);

char	*try_current_path(char *cmd)
{
	char	*get_path;
	char	*try_path;

	get_path = getcwd(NULL, 0);
	try_path = ft_strjoin(get_path, cmd);
	if (!try_path)
		return (NULL);
	if (access(try_path, F_OK) == 0 && (access(try_path, X_OK) == 0)
		&& !is_directory(try_path))
	{
		free(get_path);
		return (try_path);
	}
	free(get_path);
	free(try_path);
	return (NULL);
}

char	*correct_path(char *cmd, char *env[])
{
	int		i;
	char	**paths;
	char	*try_path;
	char	*temp;

	temp = ft_strjoin("/", cmd);
	if (!temp)
		return (NULL);
	try_path = try_current_path(temp);
	if (try_path != NULL)
		return (free_for_path(temp, NULL, try_path));
	paths = make_path(env);
	if (!paths)
		return (free_for_path(temp, NULL, NULL));
	i = -1;
	while (paths[++i])
	{
		try_path = ft_strjoin(paths[i], temp);
		if (access(try_path, F_OK) == 0)
			return (free_for_path(temp, paths, try_path));
		free(try_path);
	}
	return (free_for_path(temp, paths, NULL));
}

static char	**make_path(char *env[])
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*free_for_path(char *temp, char **paths, char *path)
{
	if (temp)
		free(temp);
	if (paths)
		free_strings(paths);
	return (path);
}

static int	is_directory(char *path)
{
	struct stat	st;

	if (lstat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}
