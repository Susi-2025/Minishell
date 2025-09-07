/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_cmd_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/07 10:28:12 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	cd_only(t_cmd *cmds);
static	int	cd_absolute(t_cmd *cmds);

int exec_cd(t_cmd *cmds)
{
	//int	i;
	// char *oldcwd;
	printf("Exec cd\n");
	if (!cmds)
		return(error_msg(cmds, 1, "cmds"));
	//if (cmds->simple_cmds[0]->args[1]== NULL )
	if (cd_only(cmds) != 0)
		return ((error_msg(cmds, 1, "cd error")));
	if (cd_absolute(cmds) != 0)
		return (error_msg(cmds, 1, "cd absolute wrong"));
	// exec_env(cmds);
	// exec_pwd(cmds);
	return (0);
}

static	int	cd_only(t_cmd *cmds)
{
	char	*home;
	char	*oldcwd;

	printf("Exec cd only\n");
	home = find_var(cmds->envp, "HOME");
	printf("%s\n", home);
	if (!home)// what happen if home wrong
		return (1);
	oldcwd = getcwd(NULL, 0);
	if (!oldcwd)
		return (1);
	if (chdir(home) != 0)
	{
		free(oldcwd);
		return (1);
	}
	else
		printf("Success change dir\n");
	if (update_env(cmds, "OLDPWD", oldcwd) != 0 || update_env(cmds, "PWD", home) != 0)
		return (1);
	free(oldcwd);
	return (0);
}

static	int	cd_absolute(t_cmd *cmds)
{
	char	*nextcwd;
	char	*oldcwd;

	printf("Exec cd absolute\n");

	nextcwd = cmds->simple_cmds[0]->args[1];
	//printf("%s\n", home);
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
	else
		printf("Success change absolute dir\n");
	if (update_env(cmds, "OLDPWD", oldcwd) != 0 || update_env(cmds, "PWD", nextcwd) != 0)
		return (1);
	free(oldcwd);
	return (0);
}

