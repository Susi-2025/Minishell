/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_io_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:30:34 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/24 20:06:09 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_file(int old_fd, char *filename, int type)
{
	int	new_fd;

	if (old_fd != -1)
		close(old_fd);
	if (type == REDIR_IN)
		new_fd = open(filename, O_RDONLY);
	else if (type == REDIR_OUT)
		new_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_APPEND)
		new_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		new_fd = -1;
	if (new_fd == -1)
		error_string(filename);
	return (new_fd);
}

static int	open_all_redirections(t_vector *redirs, t_object *pipex)
{
	int	i;
	int	type;

	i = 0;
	while (i < redirs->args_count && redirs->args[i])
	{
		type = redirs->type[i];
		if (type == REDIR_IN)
		{
			pipex->infile_fd = open_redir_file(pipex->infile_fd,
					redirs->args[i], type);
			if (pipex->infile_fd == -1)
				return (-2);
		}
		else if (type == REDIR_OUT || type == REDIR_APPEND)
		{
			pipex->outfile_fd = open_redir_file(pipex->outfile_fd,
					redirs->args[i], type);
			if (pipex->outfile_fd == -1)
				return (-2);
		}
		i++;
	}
	return (0);
}

int	handle_io_redirection(t_simple_cmd *cmd, t_object *pipex)
{
	t_vector	*redirs;

	redirs = cmd->redirections;
	if (!redirs)
		return (0);
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	if (open_all_redirections(redirs, pipex) == -2)
	{
		if (pipex->infile_fd != -1)
			close(pipex->infile_fd);
		if (pipex->outfile_fd != -1)
			close(pipex->outfile_fd);
		return (-2);
	}
	if (pipex->infile_fd != -1)
	{
		dup2(pipex->infile_fd, STDIN_FILENO);
		close(pipex->infile_fd);
	}
	if (pipex->outfile_fd != -1)
	{
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(pipex->outfile_fd);
	}
	return (0);
}
