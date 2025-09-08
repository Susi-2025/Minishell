/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:54 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/08 11:08:19 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static	int	check_built_in(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0) 
		return (1);
	if (ft_strcmp(cmd, "echo") == 0) 
		return (1);
	if (ft_strcmp(cmd, "exit") == 0) 
		return (1);
	if (ft_strcmp(cmd, "unset") == 0) 
		return (1);
	if (ft_strcmp(cmd, "export") == 0) 
		return (1);
	return (0);
}

int	exec_command(t_cmd *cmds, char **temp_env)
{
	printf("Exec cmds \n");
	if (check_built_in(cmds->simple_cmds[0]->args[0]) == 1)
		return(exec_built_in(cmds, temp_env));
	return (0);
}
