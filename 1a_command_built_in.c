/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_command_built_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/17 15:40:38 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	exec_pwd(t_shell *shell);
static	int	exec_env(t_shell *shell);
static	int	exec_export_only(t_shell *shell);

// Command will return 0 for success and non-zero for fail.
// Add checking = in the execution env to make sure only printout line which has =
// export when no option, it will sort the envp and printout.

int exec_built_in(t_shell *shell)
{
	printf("Exec export\n");
	if (!shell || !shell->cmd_args || !shell->cmd_args[0])
		return (1);
	if (ft_strcmp(shell->cmd_args[0], "pwd") == 0)
		return (exec_pwd(shell));
	else if (ft_strcmp(shell->cmd_args[0], "env") == 0)
		return (exec_env(shell));
	else if (ft_strcmp(shell->cmd_args[0], "export") == 0 && (!shell->cmd_args[1])) 
	//we need to handle the case
	//  name "viet"
	// export name;-> this will assign variable to envp.
		return (exec_export_only(shell));
			
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
	// return (0);
}

static	int	exec_pwd(t_shell *shell)
{
	char	*out;

	out = find_var(shell->envp, "PWD=");
	if (out)
		printf("%s\n", out + 4);
	else
	{
		perror("pwd");
		//error_command(shell);
		return (1);
	}
	return (0);
}

static	int	exec_env(t_shell *shell)
{
	int	i;

	if (!shell->envp)
	{
		//error_envp(shell);
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

static	int	exec_export_only(t_shell *shell)
{
	int	i;
	char	**temp;
	
	if (!shell->envp)
	{
		//error_envp(shell);
		return (1);
	}
	i  = 0;
	temp = ft_matrix_dup(shell->envp, ft_len_2d(shell->envp));
	if (!temp)
	{
		//error_malloc(shell);
		return (1);
	}
	sort_2d_array(temp);
	while (temp[i])
	{
		if (ft_strchr(temp[i], '=') && temp[i][0] != '_')
		{
			// printf("declare -x ");
			printf("%s\n", temp[i]);
		}
		i++;
	}
	ft_free_triptr(&temp);
	return (0);
}