/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_utility.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:02:33 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/19 14:14:23 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_malloc(t_shell *shell, int code)
{
	free_shell(shell);
	return (code);
}

void	free_shell(t_shell *shell)
{
	//int	i;
	
	if (!shell)
		return ;
	if (shell->envp)
		ft_free_triptr(&(shell->envp));
	if (shell->simple_cmds)
	{
		//i = 0;
		if(shell->simple_cmds[0]) // only 1 commands
		{
			if (shell->simple_cmds[0]->args)
				ft_free_triptr(&(shell->simple_cmds[0]->args));
			free(shell->simple_cmds[0]);
			//i++;
		}
		free(shell->simple_cmds);
		shell->simple_cmds = NULL;
	}
}
	

int error_msg(t_shell *shell, int code, char *str)
{
	printf("%s\n", str);
	free_shell(shell);
	return (code);
}