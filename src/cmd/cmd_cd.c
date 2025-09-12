/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/08 18:29:27 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	int	cd_only(t_cmd *cmds);
// static	int	cd_back(t_cmd *cmds);
// static	int	cd_absolute(t_cmd *cmds, char **args);

static	int	change_dir(t_cmd *cmds, char *next_wd);

int exec_cd(t_cmd *cmds, char **args)
{
	char	*next_wd;

	printf("Exec cd\n");
	if (!cmds)
		//return(error_msg(cmds, 1, "cmds"));
		return(error_msg(1, "cmds"));
	if (args[1] == NULL)
		next_wd = find_var(cmds->envp, "HOME");
	else if (ft_strcmp(args[1], "-") == 0)
	{
		next_wd = find_var(cmds->envp, "OLDPWD");
		// printf("Value of next wd: %s\n", next_wd);
	}
	else if (args[1] && ft_strcmp(args[1], "-") != 0)
		next_wd = args[1];
	if (!next_wd)
		return (1);
	if (change_dir(cmds, next_wd) == 1)
	{
		free(next_wd);
		return (1);
	}
	// if (args[1] == NULL )
	// {
	// 	if (cd_only(cmds) != 0)
	// 		//return ((error_msg(cmds, 1, "cd error")));
	// 		return ((error_msg(1, "cd error")));
	// }
	// else if (ft_strcmp(args[1], "-") == 0)
	// {
	// 	if (cd_back(cmds) != 0)
	// 		return ((error_msg(1, "cd error")));
	// }
	// else
	// {
	// 	if (cd_absolute(cmds, args) != 0)
	//  		//return (error_msg(cmds, 1, "cd absolute wrong"));
	// 		return (error_msg(1, "cd absolute wrong"));
	// }
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
		free(old_wd);
		return (1);
	}
	//printf("Change dir successful\n");
	// printf("The value of next_wd before updating env: %s\n", next_wd);
	next_wd = getcwd(NULL, 0); // update nextcwd
	if (!next_wd)
    {
        free(old_wd);
        return (1);
    }
	if (update_env(cmds, "OLDPWD", old_wd) != 0 || update_env(cmds, "PWD", next_wd) != 0)
	{
		free(old_wd);
		free(next_wd);
		return (1);
	}
	free(old_wd);
	free(next_wd);
	return (0);
}
/*
static	int	cd_only(t_cmd *cmds)
{
	char	*home;
	char	*oldcwd;

	// printf("Exec cd only\n");
	home = find_var(cmds->envp, "HOME");
	// printf("%s\n", home);
	if (!home)
		return (1);
	oldcwd = getcwd(NULL, 0);
	// printf("%s\n", oldcwd);
	if (!oldcwd)
		return (1);
	if (chdir(home) != 0)
	{
		free(oldcwd);
		return (1);
	}
	if (update_env(cmds, "OLDPWD", oldcwd) != 0 || update_env(cmds, "PWD", home) != 0)
	{
		free(oldcwd);
		return (1);
	}
	// printf("Print export to check env\n");
	// exec_export_only(cmds);
	free(oldcwd);
	return (0);
}

static	int	cd_back(t_cmd *cmds)
{
	char	*nextcwd;
	char	*oldcwd;

	// printf("Exec cd back\n");
	nextcwd = find_var(cmds->envp, "OLDPWD");
	// printf("%s\n", nextcwd);
	if (!nextcwd)
		return (1);
	oldcwd = getcwd(NULL, 0);
	if (!oldcwd)
		return (1);
	if (chdir(nextcwd) != 0)
	{
		free(oldcwd);
		return (1);
	}
	nextcwd = getcwd(NULL, 0); // update nextcwd
	if (update_env(cmds, "OLDPWD", oldcwd) != 0 || update_env(cmds, "PWD", nextcwd) != 0)
		return (1);
	free(oldcwd);
	return (0);
}

static	int	cd_absolute(t_cmd *cmds, char **args)
{
	char	*nextcwd;
	char	*oldcwd;

	// printf("Exec cd absolute\n");
	nextcwd = args[1];
	if (!nextcwd)
		return (1);
	oldcwd = getcwd(NULL, 0);
	if (!oldcwd)
		return (1);
	if (chdir(nextcwd) != 0)
	{
		free(oldcwd);
		return (1);
	}
	if (update_env(cmds, "OLDPWD", oldcwd) != 0 || update_env(cmds, "PWD", nextcwd) != 0)
		return (1);
	free(oldcwd);
	return (0);
}
*/
