/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/23 15:00:14 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*find_next_wd(t_cmd *cmds, char **args);
static	int	change_dir(t_cmd *cmds, char *next_wd);
static	char	*get_parent_dir(char **envp);

int	exec_cd(t_cmd *cmds, char **args)
{
	char	*next_wd;

	if (args[1] && args[2])
		return (error_cmd_fd(1, "cd", "", "too many arguments"));
	next_wd = find_next_wd(cmds, args);
	if (!next_wd)
		return (1);
	if (change_dir(cmds, next_wd) == 1)
		return (1);
	if (args[1])
	{
		if (ft_strcmp(args[1], "-") == 0)
			exec_pwd(cmds);
	}
	return (0);
}

static	char	*find_next_wd(t_cmd *cmds, char **args)
{
	char	*next_wd;

	next_wd = NULL;
	if ((args[1] == NULL) || (ft_strcmp(args[1], "~") == 0)
		|| (ft_strcmp(args[1], "--") == 0))
	{
		next_wd = find_var(cmds->envp, "HOME");
		if (!next_wd)
		{
			error_cmd_fd(1, "cd", "HOME", "not set");
			return (NULL);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		next_wd = find_var(cmds->envp, "OLDPWD");
		if (!next_wd)
		{
			error_cmd_fd(1, "cd", "OLDPWD", "not set");
			return (NULL);
		}
	}
	else
		next_wd = args[1];
	return (next_wd);
}

static	char	*get_parent_dir(char **envp)
{
	char	*pwd;
	char	*dup;
	char	*par_pwd;

	if (!envp)
		return (NULL);
	pwd = find_var(envp, "PWD");
	if (!pwd)
		return (NULL);
	dup = ft_strdup(pwd);
	if (!dup)
		return (NULL);
	par_pwd = ft_strjoin(dup, "/..");
	free(dup);
	if (!par_pwd)
		return (NULL);
	return (par_pwd);
}

static	int	change_dir(t_cmd *cmds, char *next_wd)
{
	char	*old_wd;
	char	*temp_wd;

	if (find_var(cmds->envp, "PWD"))
		old_wd = ft_strdup(find_var(cmds->envp, "PWD"));
	else
		return (1);
	if (chdir(next_wd) != 0)
	{
		error_cmd_fd(1, "cd", next_wd, NO_SUCH_FILE);
		return (free_2_mem(old_wd, NULL, 1));
	}
	temp_wd = getcwd(NULL, 0);
	if (!temp_wd)
	{
		ft_putstr_fd(ERR_EMPTY_FOLDER, 2);
		temp_wd = get_parent_dir(cmds->envp);
		if (!temp_wd)
			return (free_2_mem(old_wd, NULL, 1));
	}
	next_wd = temp_wd;
	if (update_env(cmds, "OLDPWD", old_wd) != 0
		|| update_env(cmds, "PWD", next_wd) != 0)
		return (free_2_mem(old_wd, next_wd, 1));
	return (free_2_mem(old_wd, next_wd, 0));
}
