/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:41:08 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/22 18:12:08 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_and_fork_logic(t_object *pipex, int i, t_cmd *cmds, char *env[])
{
	if (i < pipex->num_commands - 1)
	{
		if (pipe(pipex->pipefd) == -1)
		{
			perror("pipe error");
			exit(1);
		}
	}
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	else if (pipex->pid == 0)
		child_process(pipex, i, cmds, env);
	else
		parent_process(pipex, i);
}

int	wait_for_children(t_object *pipex)
{
	int		status;
	int		exit_code;
	pid_t	pid;

	exit_code = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == pipex->last_child_pid)
			exit_code = WEXITSTATUS(status);
		pid = wait(&status);
	}
	return (exit_code);
}

int	ft_pipex(t_cmd *cmds, char **env[])
{
	t_object	pipex;
	int			i;
	char		**args;

	if (!cmds)
		return (1);
	fire_up_pipeinator(&pipex, cmds);
	i = 0;
	while (i < pipex.num_commands)
	{
		args = cmds->simple_cmds[i]->args;
		if (cmds->cmds_count == 1 && check_built_in(args[0]) == 1)
		{
			cmds->err_code = exec_parent(cmds, args, env, &pipex);
			last_close(&pipex);
			return (cmds->err_code);
		}
		else
			pipe_and_fork_logic(&pipex, i, cmds, *env);
		i++;
	}
	last_close(&pipex);
	return (wait_for_children(&pipex));
}
