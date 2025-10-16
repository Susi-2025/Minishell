/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/16 12:15:47 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	change_dir(t_cmd *cmds, char *next_wd);
static	int	free_2_mem(char *old_wd, char *next_wd, int exit_code);

int	exec_cd(t_cmd *cmds, char **args)
{
	char	*next_wd;

	next_wd = NULL;
	if (!cmds)
		return (error_msg(1, "cmds"));
	if (args[1] == NULL)
	{
		next_wd = find_var(cmds->envp, "HOME");
		return (error_string_cd("HOME", 1));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		next_wd = find_var(cmds->envp, "OLDPWD");
		return (error_string_cd("OLDPWD", 1));
	}
	else if (args[1] && ft_strcmp(args[1], "-") != 0)
		next_wd = args[1];
	if (!next_wd)
		return (1);
		// return (error_string_cd(NULL, 1));
	if (change_dir(cmds, next_wd) == 1)
		return (1);
	return (0);
}

static	int	change_dir(t_cmd *cmds, char *next_wd)
{
	char	*old_wd;

	old_wd = getcwd(NULL, 0);
	if (!old_wd)
		return (1);
	if (chdir(next_wd) != 0)
	{
		perror("cd");
		return (free_2_mem(old_wd, NULL, 1));
	}
	next_wd = getcwd(NULL, 0);
	if (!next_wd)
		return (free_2_mem(old_wd, NULL, 1));
	if (update_env(cmds, "OLDPWD", old_wd) != 0
		|| update_env(cmds, "PWD", next_wd) != 0)
		return (free_2_mem(old_wd, next_wd, 1));
	return (free_2_mem(old_wd, next_wd, 0));
}

static	int	free_2_mem(char *old_wd, char *next_wd, int exit_code)
{
	if (old_wd)
		free(old_wd);
	if (next_wd)
		free(next_wd);
	return (exit_code);
}
