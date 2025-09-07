/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_err_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:02:33 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/07 15:50:56 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_malloc(t_cmd *cmds, int code)
{
	//free_shell(cmds);
	free_cmd(cmds);
	return (code);
}

// void	free_shell(t_cmd *cmds)
// {
// 	//int	i;
	
// 	if (!cmds)
// 		return ;
// 	if (cmds->envp)
// 		ft_free_triptr(&(cmds->envp));
// 	if (cmds->simple_cmds)
// 	{
// 		//i = 0;
// 		if(cmds->simple_cmds[0]) // only 1 commands
// 		{
// 			if (cmds->simple_cmds[0]->args)
// 				ft_free_triptr(&(cmds->simple_cmds[0]->args));
// 			free(cmds->simple_cmds[0]);
// 			//i++;
// 		}
// 		free(cmds->simple_cmds);
// 		cmds->simple_cmds = NULL;
// 	}
// }

int error_msg(t_cmd *cmds, int code, char *str)
{
	printf("%s\n", str);
	free_cmd(cmds);
	//free_shell(cmds);
	return (code);
}