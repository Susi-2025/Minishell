/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_command_built_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/19 16:03:03 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	exec_pwd(t_shell *shell);
static	int	exec_env(t_shell *shell);

//1. Command will return 0 for success and non-zero for fail.
//2. "env": Add checking = to make sure only printout line which has =
//3. "export, echo, cd"->separatre to new file


int exec_built_in(t_shell *shell)
{
	printf("Exec built-in\n");
	// if (!shell || !shell->cmd_args || !shell->cmd_args[0])
	// 	return(error_msg(shell, 1, "shell"));;
	// if (ft_strcmp(shell->cmd_args[0], "pwd") == 0)
	// 	return (exec_pwd(shell));
	// else if (ft_strcmp(shell->cmd_args[0], "env") == 0)
	// 	return (exec_env(shell));
	// else if (ft_strcmp(shell->cmd_args[0], "export") == 0 && (!shell->cmd_args[1])) 
	// 	return (exec_export_only(shell));
	// else if (ft_strcmp(shell->cmd_args[0], "echo") == 0)
	// return (exec_echo(shell));
	// else if (ft_strcmp(shell->cmd_args[0], "cd") == 0)
	// 	exec_cd(shell);
	return (exec_cd(shell)); // ok
	return (exec_echo(shell)); //ok
	return (exec_export_only(shell));//work-but no same as bash, need to change
	return (exec_env(shell));// ok
	return (exec_pwd(shell));//ok
	// if (ft_strcmp(shell->cmd_args[0], "exit") == 0)
	// 	exec_exit(shell);
	// if (ft_strcmp(shell->cmd_args[0], "unset") == 0)
	// 	exec_unset(shell);
	return (0);
}

static	int	exec_pwd(t_shell *shell)
// int	exec_pwd(t_shell *shell)
{
	char	*out;

	out = find_var(shell->envp, "PWD=");
	if (out)
		printf("%s\n", out);
	else
		return(error_msg(shell, 1, "pwd"));
	return (0);
}

static	int	exec_env(t_shell *shell)
// int	exec_env(t_shell *shell)
{
	int	i;

	if (!shell->envp)
		return(error_msg(shell, 1, "envp"));
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strchr(shell->envp[i], '='))
			printf("%s\n", shell->envp[i]);
		i++;
	}
	return (0);
}
