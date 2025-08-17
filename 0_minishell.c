/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:31:23 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/17 15:52:24 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	int	len;
	t_shell shell;
	
	(void)av;
	if (ac)
		printf("Welcome to Minishell, we have %d arguments\n", ac);
	len = ft_len_2d(envp);
	shell.envp = ft_matrix_dup(envp, len);
	if (!shell.envp)
	{
		error_malloc(&shell);
		return (1);
	}
	exec_command(&shell);
	// free_shell(&shell);
	return (0);
}
