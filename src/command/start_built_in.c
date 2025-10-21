/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:54 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/21 11:05:24 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_built_in(char *cmd)
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

void	exec_parent(t_cmd *cmds, char **args, char **env[], int args_count)
{
	int	exit_code;

	if ((ft_strcmp(args[0], "exit") == 0) && (args_count <= 2))
	{
		exit_code = exec_built_in(cmds, args, env, args_count);
		ft_free_triptr(env);
		free_cmd(cmds);
		exit (exit_code);
	}
	// else if (ft_strcmp(args[0], "exit") == 0 && args_count > 2)
	// {
	// 	// exit_code = 
	// 	exec_built_in(cmds, args, env, args_count);
	// 	// ft_free_triptr(env);
	// 	// free_cmd(cmds);
	// 	// exit (exit_code);
	// }
	else
		exec_built_in(cmds, args, env, args_count);
}
