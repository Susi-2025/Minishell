/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_command_built_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/18 11:02:44 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	exec_pwd(t_shell *shell);
static	int	exec_env(t_shell *shell);
// static	int exec_echo(t_shell *shell);
// static	void	echo_stored_var(char **envp, char *string);

//1. Command will return 0 for success and non-zero for fail.
//2. "env": Add checking = to make sure only printout line which has =
//3. "export"->separatre to new file
//4. "echo"-> only print the character input, not yet the stored variable

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
	// else if (ft_strcmp(shell->cmd_args[0], "unset") == 0)
		return (exec_unset(shell));
		return (exec_echo(shell));
		return (exec_export_only(shell));
		return (exec_env(shell));
		return (exec_pwd(shell));
	// else if (ft_strcmp(shell->cmd_args[0], "cd") == 0)
	// 	exec_cd(shell);
	// if (ft_strcmp(shell->cmd_args[0], "exit") == 0)
	// 	exec_exit(shell);
	// if (ft_strcmp(shell->cmd_args[0], "unset") == 0)
	// 	exec_unset(shell);
	return (0);
}

static	int	exec_pwd(t_shell *shell)
{
	char	*out;

	out = find_var(shell->envp, "PWD=");
	if (out)
		printf("%s\n", out + 4);
	else
		return(error_msg(shell, 1, "pwd"));
	return (0);
}

static	int	exec_env(t_shell *shell)
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

// static	int exec_echo(t_shell *shell)
// {
// 	int	i;
		
// 	if (!shell)
// 		return(error_msg(shell, 1, "shell"));
// 	i = 1;
// 	while(shell->cmd_args[i])
// 	{
// 		if(shell->cmd_args[i][0] == '$')
// 			echo_stored_var(shell->envp, &(shell->cmd_args[i][1]));
// 		else
// 			printf("%s", shell->cmd_args[i]);
// 		if (i < (ft_len_2d(shell->cmd_args) - 1))
// 			printf(" ");
// 		i++;
// 	}
// 	printf("\n");
// 	return (0);
// }

// static	void	echo_stored_var(char **envp, char *string)
// {
// 	char	*temp;
// 	char	*sub_temp;
	
// 	temp = find_var(envp, string);
// 	if (temp != NULL)
// 	{
// 		sub_temp = ft_strchr(temp, '=');
// 		if (sub_temp && (sub_temp + 1))
// 			printf("%s", sub_temp + 1);
// 	}
// }