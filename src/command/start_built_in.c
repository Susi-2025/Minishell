/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:54 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/21 20:39:55 by vinguyen         ###   ########.fr       */
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

int	exec_parent(t_cmd *cmds, char **args, char **env[], t_object *pipex)
{
	int	exit_code;
	int	args_count;
	int orig_stdin;
    int orig_stdout;

    // 1. SAVE the original terminal FDs
    orig_stdin = dup(STDIN_FILENO);
    orig_stdout = dup(STDOUT_FILENO);
    if (orig_stdin == -1 || orig_stdout == -1)
    {
        perror("dup");
        return (1); // Failed to save, exit
    }
	args_count = cmds->simple_cmds[0]->args_count;
	if (handle_io_redirection(cmds->simple_cmds[0], pipex, cmds, *env) == -2)
	{
        // 3a. RESTORE FDs even on redirection failure
        dup2(orig_stdin, STDIN_FILENO);
        dup2(orig_stdout, STDOUT_FILENO);
        close(orig_stdin);
        close(orig_stdout);
        return (1); // Return the failure code
    }
	exit_code = exec_built_in(cmds, args, env, args_count);
	dup2(orig_stdin, STDIN_FILENO);
    dup2(orig_stdout, STDOUT_FILENO);
    close(orig_stdin);
    close(orig_stdout);
	return (exit_code);
}
