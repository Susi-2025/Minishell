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

static	int	change_dir(t_cmd *cmds, char *next_wd);

int	exec_cd(t_cmd *cmds, char **args)
{
	char	*next_wd;

	//printf("Exec cd\n");
	if (!cmds)
		//return(error_msg(cmds, 1, "cmds"));
		return (error_msg(1, "cmds"));
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
	if (update_env(cmds, "OLDPWD", old_wd) != 0
		|| update_env(cmds, "PWD", next_wd) != 0)
	{
		free(old_wd);
		free(next_wd);
		return (1);
	}
	free(old_wd);
	free(next_wd);
	return (0);
}
