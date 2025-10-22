/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:31:50 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/22 18:10:14 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cmd(t_object *pipex, int i, t_cmd *cmds, char *env[])
{
	char	**args;
	int		args_count;
	int		exit_code;

	(void)pipex;
	if (i >= cmds->cmds_count || !cmds->simple_cmds[i])
	{
		error_string("Invalid command index.");
		exit(127);
	}
	args = cmds->simple_cmds[i]->args;
	args_count = cmds->simple_cmds[i]->args_count;
	if (check_built_in(args[0]) == 1)
	{
		exit_code = exec_built_in(cmds, args, &env, args_count);
		free_cmd(cmds);
		ft_free_triptr(&env);
		exit(exit_code);
	}
	else
	{
		exec_external(cmds, args, env);
		free_and_exit(cmds, env, 127);
	}
}

int	open_last_file(t_vector *files, int flags, t_cmd *cmds, char *env[])
{
	int	i;
	int	last_fd;

	(void)cmds;
	(void)env;
	if (!files)
		return (-1);
	i = 0;
	last_fd = -1;
	while (i < files->args_count)
	{
		if (last_fd != -1)
			close(last_fd);
		if (flags & O_CREAT)
		{
			if (files->type[i] == REDIR_APPEND)
				last_fd = open(files->args[i], O_WRONLY | O_CREAT | O_APPEND,
						0644);
			else if (files->type[i] == REDIR_OUT)
				last_fd = open(files->args[i], O_WRONLY | O_CREAT | O_TRUNC,
						0644);
		}
		else
			last_fd = open(files->args[i], flags);
		if (last_fd == -1)
		{
			error_string(files->args[i]);
			return (-2);
		}
		i++;
	}
	return (last_fd);
}

int	handle_io_redirection(t_simple_cmd *cmd, t_object *pipex, t_cmd *cmds,
		char *env[])
{
	pipex->infile_fd = open_last_file(cmd->in_file, O_RDONLY, cmds, env);
	if (pipex->infile_fd == -2)
		return (-2);
	if (pipex->infile_fd != -1)
	{
		dup2(pipex->infile_fd, STDIN_FILENO);
		close(pipex->infile_fd);
	}
	pipex->outfile_fd = open_last_file(cmd->out_file,
			O_WRONLY | O_CREAT | O_TRUNC, cmds, env);
	if (pipex->outfile_fd == -2)
		return (-2);
	if (pipex->outfile_fd != -1)
	{
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(pipex->outfile_fd);
	}
	return (0);
}

void	child_process(t_object *pipex, int i, t_cmd *cmds, char *env[])
{
	if (i > 0)
	{
		dup2(pipex->prev_pipe_in, STDIN_FILENO);
		close(pipex->prev_pipe_in);
	}
	if (i != pipex->num_commands - 1)
		dup2(pipex->pipefd[1], STDOUT_FILENO);
	if (i != pipex->num_commands - 1)
	{
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
	}
	if (handle_io_redirection(cmds->simple_cmds[i], pipex, cmds, env) == -2)
		free_and_exit(cmds, env, 1);
	if (cmds->simple_cmds[i]->args[0] != NULL)
		run_cmd(pipex, i, cmds, env);
	else
		free_and_exit(cmds, env, 0);
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
