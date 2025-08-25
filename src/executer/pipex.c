/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:41:08 by cdohanic          #+#    #+#             */
/*   Updated: 2025/07/03 14:29:29 by cdohanic         ###   ########.fr       */
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
	// printf("DEBUG: Before waiting, last_child_pid = %d\n", pipex->last_child_pid);
	// printf("DEBUG: About to enter while(wait...)\n");
	while (wait(&pipex->status) > 0)
	{
		// printf("DEBUG: wait() collected a child\n");
	}
	// printf("DEBUG: Finished waiting\n");
	int exit_code = WEXITSTATUS(pipex->last_status);
	// printf("DEBUG: Returning exit code: %d\n", exit_code);
	return (exit_code);
}

int	ft_pipex(t_cmd *cmds, char *env[])
{
	t_object	pipex;
	int			i;

	if (!cmds  || cmds->cmds_count < 1)
		return (1);
	
	fd_init(&pipex.infile_fd, &pipex.outfile_fd, cmds->in_file, cmds->out_file);
	fire_up_pipeinator(&pipex, cmds);
	i = 0;
	while (i < pipex.num_commands)
	{
		pipe_and_fork_logic(&pipex, i, cmds, env);
		i++;
	}
	last_close(&pipex);
	// if (pipex.last_child_pid != -1)
	// 	waitpid(pipex.last_child_pid, &pipex.last_status, 0);
	// while (wait(&pipex.status) > 0)
	// 	;
	// return (WEXITSTATUS(pipex.last_status));
	// exit(WEXITSTATUS(pipex.last_status));

    return (wait_for_children(&pipex));
}
