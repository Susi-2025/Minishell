/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_cmd_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/19 16:02:34 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	cd_only(t_shell *shell);

int exec_cd(t_shell *shell)
{
	//int	i;
	// char *oldcwd;
	printf("Exec cd\n");
	if (!shell)
		return(error_msg(shell, 1, "shell"));
	//if (shell->simple_cmds[0]->args[1]== NULL )
	if (cd_only(shell) != 0)
		return ((error_msg(shell, 1, "cd error")));
	// exec_env(shell);
	// exec_pwd(shell);
	return (0);
}

static	int	cd_only(t_shell *shell)
{
	char	*home;
	char	*oldcwd;

	printf("Exec cd only\n");
	home = find_var(shell->envp, "HOME");
	printf("%s\n", home);
	if (!home)
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
	if (update_env(shell, "OLDPWD", oldcwd) != 0 || update_env(shell, "PWD", home) != 0)
		return (1);
	free(oldcwd);
	return (0);
}

