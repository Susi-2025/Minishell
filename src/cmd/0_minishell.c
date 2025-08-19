/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:31:23 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/19 15:59:11 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	init_shell(t_shell *shell, char **envp)
{
	int	 len;
	
	len = ft_len_2d(envp);
	shell->envp = ft_matrix_dup(envp, len);
	if (!shell->envp)
		return(error_malloc(shell, 1));
	
	shell->simple_cmds = malloc(sizeof(t_simple_cmd *) * 2); // only 1 cmd
	if (!shell->simple_cmds)
        return (error_malloc(shell, 1));
		
	shell->simple_cmds[0]= malloc(sizeof(t_simple_cmd));
	if (!shell->simple_cmds[0])
        return (error_malloc(shell, 1));
	shell->simple_cmds[1] = NULL; // terminate
	
	// shell->simple_cmds[0]->args_count = 5;
    // shell->simple_cmds[0]->args_capacity = 6;
	shell->simple_cmds[0]->args = malloc(sizeof(char *) * 6);
    if (!shell->simple_cmds[0]->args)
    {
		return (error_malloc(shell, 1));
	}
	shell->simple_cmds[0]->args[0] = strdup("echo");
	shell->simple_cmds[0]->args[1] = strdup("USER");
	shell->simple_cmds[0]->args[2] = strdup("$PWD");
	shell->simple_cmds[0]->args[3] = strdup("abcde");
	shell->simple_cmds[0]->args[4] = strdup("$PWD23");
	shell->simple_cmds[0]->args[5] = NULL;
	return (0);
}

int main(int ac, char **av, char **envp)
{
	//int	len;
	t_shell shell = {0};
	
	(void)av;
	if (ac)
		printf("Welcome to Minishell, we have %d arguments\n", ac);
	if (init_shell(&shell, envp))
		return (1);
	exec_command(&shell);
	printf("Finish exec\n");
	free_shell(&shell);
	//ft_free_triptr(&shell.envp);
	return (0);
}
