/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_minishell_viet.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:31:23 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/07 10:29:35 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	init_shell(t_cmd *cmds, char **envp)
{
	int	 len;
	
	len = ft_len_2d(envp);
	cmds->envp = ft_matrix_dup(envp, len);
	if (!cmds->envp)
		return(error_malloc(cmds, 1));
	
	cmds->simple_cmds = malloc(sizeof(t_simple_cmd *) * 2); // only 1 cmd
	if (!cmds->simple_cmds)
        return (error_malloc(cmds, 1));
		
	cmds->simple_cmds[0]= malloc(sizeof(t_simple_cmd));
	if (!cmds->simple_cmds[0])
        return (error_malloc(cmds, 1));
	cmds->simple_cmds[1] = NULL; // terminate
	
	// cmds->simple_cmds[0]->args_count = 5;
    // cmds->simple_cmds[0]->args_capacity = 6;
	cmds->simple_cmds[0]->args = malloc(sizeof(char *) * 6);
    if (!cmds->simple_cmds[0]->args)
    {
		return (error_malloc(cmds, 1));
	}
	cmds->simple_cmds[0]->args[0] = strdup("echo");
	cmds->simple_cmds[0]->args[1] = strdup("USER");
	cmds->simple_cmds[0]->args[2] = strdup("$PWD");
	cmds->simple_cmds[0]->args[3] = strdup("abcde");
	cmds->simple_cmds[0]->args[4] = strdup("$PWD23");
	cmds->simple_cmds[0]->args[5] = NULL;
	return (0);
}

int main_2(int ac, char **av, char **envp)
{
	//int	len;
	t_cmd cmds = {0};
	
	(void)av;
	if (ac)
		printf("Welcome to Minishell, we have %d arguments\n", ac);
	if (init_cmd(&cmds, envp))
		return (1);
	exec_command(&cmds);
	printf("Finish exec\n");
	free_shell(&cmds);
	//ft_free_triptr(&cmds.envp);
	return (0);
}
