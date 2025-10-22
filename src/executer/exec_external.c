/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:57:04 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/22 16:57:24 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(t_cmd *cmds, char **args, char *env[]);
static char	*check_cmd_only(t_cmd *cmds, char *arg, char *env[]);

void	exec_external(t_cmd *cmds, char **args, char *env[])
{
	char		*path;

	path = find_path(cmds, args, env);
	execve(path, args, env);
	if (errno == ENOENT)
	{
		if (!path_exists(env))
			error_string(args[0]);
		else
			failed_exec(args[0]);
	}
	else
	{
		error_string(args[0]);
		free_and_exit(cmds, env, 126);
	}
}

static char	*find_path(t_cmd *cmds, char **args, char *env[])
{
	char		*path;
	struct stat	st;

	path = check_cmd_only(cmds, args[0], env);
	if (!path)
		path = correct_path(args[0], env);
	if (path != NULL)
	{
		free(args[0]);
		args[0] = path;
	}
	else
		handle_cmd_error(cmds, args[0], env, 127);
	if (lstat(args[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		fprintf(stderr, "%s: Is a directory\n", args[0]);
		free_and_exit(cmds, env, 126);
	}
	return (args[0]);
}

static char	*check_cmd_only(t_cmd *cmds, char *arg, char *env[])
{
	char	*out;

	if (!arg || !cmds)
		return (NULL);
	if (arg[0] == '/' || (arg[0] == '.' && arg[1] == '/'))
	{
		if (access(arg, X_OK) == 0)
		{
			out = ft_strdup(arg);
			if (!out)
				return (NULL);
			return (out);
		}
		else if (access(arg, F_OK) == 0)
		{
			out = ft_strdup(arg);
			if (!out)
				return (NULL);
			return (out);
		}
		handle_no_file(cmds, arg, env, 127);
	}
	return (NULL);
}
