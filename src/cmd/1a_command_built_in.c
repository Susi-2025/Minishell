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
static	int	exec_unset(t_shell *shell);
static	int	exec_exit(t_shell *shell, char *s);

//1. Command will return 0 for success and non-zero for fail.
//2. "env": Add checking = to make sure only printout line which has =
//3. "export, echo, cd"->separatre to new file


int exec_built_in(t_shell *shell)
{
	printf("Exec built-in\n");
	// if (!shell || !shell->cmd_args || !shell->simple_cmds[0]->args[0])
	// 	return(error_msg(shell, 1, "shell"));;
	// if (ft_strcmp(shell->simple_cmds[0]->args[0], "pwd") == 0)
	// 	return (exec_pwd(shell));
	// else if (ft_strcmp(shell->simple_cmds[0]->args[0], "env") == 0)
	// 	return (exec_env(shell));
	// else if (ft_strcmp(shell->simple_cmds[0]->args[0], "export") == 0 && (!shell->simple_cmds[0]->args[1])) 
	// 	return (exec_export_only(shell));
	// else if (shell->simple_cmds[0]->args[0], "echo") == 0)
	// return (exec_echo(shell));
	// else if (shell->simple_cmds[0]->args[0], "cd") == 0)
	// 	exec_cd(shell);
	// else if (shell->simple_cmds[0]->args[0], "unset") == 0)
	// 	exec_unset(shell);
	// else if (shell->simple_cmds[0]->args[0], "exit") == 0)
	// 	exec_exit(shell);
	return (exec_exit(shell, shell->simple_cmds[0]->args[1]));//not yet testing
	return (exec_unset(shell));// partly ok
	return (exec_cd(shell)); // ok
	return (exec_echo(shell)); //ok
	return (exec_export_only(shell));//work-but no same as bash, need to change
	return (exec_env(shell));// ok
	return (exec_pwd(shell));//ok
	// if (ft_strcmp(shell->cmd_args[0], "exit") == 0)
	// 	exec_exit(shell);
	// if (shell->simple_cmds[0]->args[0], "unset") == 0)
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
// only works if cmd[0]->args[1] receive PATH-> not the expansion value
static	int	exec_unset(t_shell *shell)
{
	printf("Unset running\n");
	printf("Before unset USER\n");
	exec_env(shell);
	printf("\n");
	// if (!shell->envp || !shell->simple_cmds[0]->args[1])
	// 	return (1);
	// else
	// return(reduce_env(shell, shell->simple_cmds[0]->args[1]));
	int res = reduce_env(shell, shell->simple_cmds[0]->args[1]);
	printf("After unset USER\n");
	printf("\n");
	exec_env(shell);
	return (res);
}

//not good
static	int	exec_exit(t_shell *shell, char *s)
{
	int	status;

	printf("exit\n");
	if (s && ft_is_numeric(s))
		status = ft_atoi(s);
	else if (s)
	{
		printf("bash: exit: %s: numeric argument required\n", s);
		status = 2;
	}
	else
		status = 0;
	free_shell(shell);
	exit(status);
	return (0);
}