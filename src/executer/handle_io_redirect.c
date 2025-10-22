/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_io_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:30:34 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/22 18:30:58 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	find_fd(int *last_fd, int flags, int i, t_vector *files);

// int	open_last_file(t_vector *files, int flags, t_cmd *cmds, char *env[])
// {
// 	int	i;
// 	int	last_fd;

// 	(void)cmds;
// 	(void)env;
// 	if (!files)
// 		return (-1);
// 	i = 0;
// 	last_fd = -1;
// 	while (i < files->args_count)
// 	{
// 		last_fd = find_fd(&last_fd, flags, i, files);
// 		if (last_fd == -1)
// 		{
// 			error_string(files->args[i]);
// 			return (-2);
// 		}
// 		i++;
// 	}
// 	return (last_fd);
// }

// static int	find_fd(int *last_fd, int flags, int i, t_vector *files)
// {
// 	if (*last_fd != -1)
// 		close(*last_fd);
// 	if (flags & O_CREAT)
// 	{
// 		if (files->type[i] == REDIR_APPEND)
// 			*last_fd = open(files->args[i], O_WRONLY | O_CREAT | O_APPEND,
// 					0644);
// 		else if (files->type[i] == REDIR_OUT)
// 			*last_fd = open(files->args[i], O_WRONLY | O_CREAT | O_TRUNC,
// 					0644);
// 	}
// 	else
// 		*last_fd = open(files->args[i], flags);
// 	return (*last_fd);
// }

// int	handle_io_redirection(t_simple_cmd *cmd, t_object *pipex, t_cmd *cmds,
// 		char *env[])
// {
// 	pipex->infile_fd = open_last_file(cmd->in_file, O_RDONLY, cmds, env);
// 	if (pipex->infile_fd == -2)
// 		return (-2);
// 	if (pipex->infile_fd != -1)
// 	{
// 		dup2(pipex->infile_fd, STDIN_FILENO);
// 		close(pipex->infile_fd);
// 	}
// 	pipex->outfile_fd = open_last_file(cmd->out_file,
// 			O_WRONLY | O_CREAT | O_TRUNC, cmds, env);
// 	if (pipex->outfile_fd == -2)
// 		return (-2);
// 	if (pipex->outfile_fd != -1)
// 	{
// 		dup2(pipex->outfile_fd, STDOUT_FILENO);
// 		close(pipex->outfile_fd);
// 	}
// 	return (0);
// }

static int  open_redir_file(int old_fd, char *filename, int type)
{
    int new_fd;

    if (old_fd != -1)
        close(old_fd);
    if (type == REDIR_IN)
        new_fd = open(filename, O_RDONLY);
    else if (type == REDIR_OUT)
        new_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (type == REDIR_APPEND)
        new_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        new_fd = -1; // Should not happen
    if (new_fd == -1)
        error_string(filename); // Print error here
    return (new_fd);
}

static int  open_all_redirections(t_vector *redirs, t_object *pipex)
{
    int     i;
    int     type;

    i = 0;
    while (i < redirs->args_count)
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

int handle_io_redirection(t_simple_cmd *cmd, t_object *pipex, t_cmd *cmds,
        char *env[])
{
    t_vector    *redirs;

    (void)cmds;
    (void)env;

    redirs = cmd->redirections;
    if (!redirs)
        return (0);
    pipex->infile_fd = -1;
    pipex->outfile_fd = -1;
    if (open_all_redirections(redirs, pipex) == -2)
        return (-2);
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