/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:54 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/23 18:27:05 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	dup_std(int orig_stdin, int orig_stdout);

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

int	exec_parent(t_cmd *cmds, char **args, char **env[], t_object *pipex)
{
	int	exit_code;
	int	args_count;

	cmds->orig_stdin = dup(STDIN_FILENO);
	cmds->orig_stdout = dup(STDOUT_FILENO);
	if (cmds->orig_stdin == -1 || cmds->orig_stdout == -1)
	{
		perror("dup");
		return (1);
	}
	args_count = cmds->simple_cmds[0]->args_count;
	if (handle_io_redirection(cmds->simple_cmds[0], pipex) == -2)
	{
		dup_std(cmds->orig_stdin, cmds->orig_stdout);
		return (1);
	}
	exit_code = exec_built_in(cmds, args, env, args_count);
	dup_std(cmds->orig_stdin, cmds->orig_stdout);
	return (exit_code);
}

static	void	dup_std(int orig_stdin, int orig_stdout)
{
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
}
