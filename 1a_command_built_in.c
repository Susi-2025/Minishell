/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_command_built_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/17 13:01:29 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	exec_pwd(t_shell *shell);
static	int	exec_env(t_shell *shell);

// Command will return 0 for success and non-zero for fail.
// Add checking = in the execution env to make sure only printout line which has =

int exec_built_in(t_shell *shell)
{
	if (!shell || !shell->cmd_args || !shell->cmd_args[0])
		return (1);
	//if (ft_strcmp(shell->cmd_args[0], "pwd") == 0)
	return (exec_pwd(shell));
	// else if (ft_strcmp(shell->cmd_args[0], "env") == 0)
	return (exec_env(shell));
		
	// else if (ft_strcmp(shell->cmd_args[0], "cd") == 0)
	// 	exec_cd(shell);
	// if (ft_strcmp(shell->cmd_args[0], "env") == 0)
	// 	exec_env(shell);
	// if (ft_strcmp(shell->cmd_args[0], "echo") == 0)
	// 	exec_echo(shell);
	// if (ft_strcmp(shell->cmd_args[0], "exit") == 0)
	// 	exec_exit(shell);
	// if (ft_strcmp(shell->cmd_args[0], "unset") == 0)
	// 	exec_unset(shell);
	// if (ft_strcmp(shell->cmd_args[0], "export") == 0)
	// 	exec_export(shell);
	// return (0);
}

static	int	exec_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = find_var(shell->envp, "PWD");
	if (pwd)
		printf("%s\n", pwd + 4);
	else
	{
		perror("pwd");
		error_command(shell);
		return (1);
	}
	return (0);
}

static	int	exec_env(t_shell *shell)
{
	int	i;

	if (!shell->envp)
	{
		error_envp(shell);
		return (1);
	}
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strchr(shell->envp[i], '='))
			printf("%s\n", shell->envp[i]);
		i++;
	}
	return (0);
}