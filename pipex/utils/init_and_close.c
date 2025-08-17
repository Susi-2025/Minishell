/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:29:14 by cdohanic          #+#    #+#             */
/*   Updated: 2025/07/03 14:10:06 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	fd_init(int *infile_fd, int *outfile_fd, char *in, char *out)
{
	*outfile_fd = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile_fd == -1)
		error_string(out);
	*infile_fd = open(in, O_RDONLY);
	if (*infile_fd == -1)
		error_string(in);
}

void	last_close(t_object *pipex)
{
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	if (pipex->num_commands > 1)
		close(pipex->prev_pipe_in);
}

void	fire_up_pipeinator(t_object *pipex, int argc)
{
	pipex->last_child_pid = -1;
	pipex->num_commands = argc -3;
	pipex->prev_pipe_in = pipex->infile_fd;
	pipex->last_status = 0;
}
