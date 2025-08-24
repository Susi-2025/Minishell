/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:31:50 by cdohanic          #+#    #+#             */
/*   Updated: 2025/07/03 14:19:05 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	run_cmd(t_object *pipex, int i, t_cmd *cmds, char *env[])
{

	char	**args;

	//Eliminate this struct
	(void)pipex;
	if (i >= cmds->cmds_count || !cmds->simple_cmds[i])
	{
		error_string("Invalid command index.");
		exit(127);
	}

	args = cmds->simple_cmds[i]->args;
	args[0] = correct_path(args[0], env);
	if (!args[0])
	{
		error_string(args[0]);
		exit(127);
	}


	execve(args[0], args, env);

	if (errno == ENOENT)
	{
		if (!path_exists(env))
			error_string(args[0]);
		else
			failed_exec(args[0]);
	}
	else
		error_string(args[0]);
	exit(127);
}

void	reading_pipe(t_object *pipex, int i)
{
	if (i != 0)
	{
		dup2(pipex->prev_pipe_in, STDIN_FILENO);
		close(pipex->prev_pipe_in);
	}
	else
	{
		if (pipex->infile_fd == -1)
			exit(1);
		dup2(pipex->infile_fd, STDIN_FILENO);
		close(pipex->infile_fd);
	}
}

void	writing_pipe(t_object *pipex, int i)
{
	if (i == pipex->num_commands - 1)
	{
		if (pipex->outfile_fd == -1)
			exit(1);
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(pipex->outfile_fd);
	}
	else
	{
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close(pipex->pipefd[1]);
		close(pipex->pipefd[0]);
	}
}

void	child_process(t_object *pipex, int i, t_cmd *cmds, char *env[])
{
	reading_pipe(pipex, i);
	writing_pipe(pipex, i);
	run_cmd(pipex, i, cmds, env);
}

void	parent_process(t_object *pipex, int i)
{
	if (i > 0)
		close(pipex->prev_pipe_in);
	if (i < pipex->num_commands - 1)
	{
		pipex->prev_pipe_in = pipex->pipefd[0];
		close(pipex->pipefd[1]);
	}
	if (i == pipex->num_commands - 1)
		pipex->last_child_pid = pipex->pid;
}
