/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:31:23 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/07 17:56:40 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_envp(t_cmd *cmds, char **envp)
{
	int	 len;
	
	len = ft_len_2d(envp);
	printf("Len of envp: %d\n", len);
	cmds->envp = ft_matrix_dup(envp, len);
	if (!cmds->envp)
		return(error_malloc(cmds, 1));
	// int i = 0;
	// len = ft_len_2d(envp);
	// while (i< len)
	// {
	// 	printf("Value of envp at %d position is: %s\n", i, envp[i]);
	// 	i++;
	// }
	// printf("Finish initial envp\n");
	return (0);
}

// int temp(int ac, char **av, char **envp)
// {
// 	//int	len;
// 	t_cmd cmds = {0};
	
// 	(void)av;
// 	if (ac)
// 		printf("Welcome to Minishell, we have %d arguments\n", ac);
// 	if (init_cmd(&cmds, envp))
// 		return (1);
// 	exec_command(&cmds);
// 	printf("Finish exec\n");
// 	free_shell(&cmds);
// 	//ft_free_triptr(&cmds.envp);
// 	return (0);
// }
