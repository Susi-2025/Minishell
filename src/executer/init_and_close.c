/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:29:14 by cdohanic          #+#    #+#             */
/*   Updated: 2025/09/09 16:47:08 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int create_heredoc_fd_direct(t_cmd *cmds)
{
    int pipefd[2];
    
    if (pipe(pipefd) == -1)
        return (-1);
    
    // Write heredoc content to write end
    if (cmds->here_doc_cont)
    {
        write(pipefd[1], cmds->here_doc_cont, ft_strlen(cmds->here_doc_cont));
    }
    close(pipefd[1]); // close write end
    
    return (pipefd[0]); // return read end
}

void	fd_init(int *infile_fd, int *outfile_fd, t_object* pipex, t_cmd *cmds)
{
	int i;
	int	fd;

	i = 0;
	*infile_fd = -1;
	*outfile_fd = -1;
	pipex->status[0] = FILE_NONE;
	pipex->status[1] = FILE_NONE;
	if (cmds->out_file != NULL)
	{
		while (i < cmds->out_file->args_count)
		{
			fd = open(cmds->out_file->args[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				error_string(cmds->out_file->args[i]);
				pipex->status[1] = FILE_ERROR;
				return;
			}
			i++;
			if (i != cmds->out_file->args_count)
				close(fd);
			else
			{
				*outfile_fd = fd;
				pipex->status[1] = FILE_VALID;
			}
		}
	}

	i = 0;	
	if (cmds->here_doc && cmds->here_doc_cont)
	 	*infile_fd = create_heredoc_fd_direct(cmds);
	else if (cmds->in_file != NULL)
	{
		while (i < cmds->in_file->args_count)
		{
			fd = open(cmds->in_file->args[i], O_RDONLY);
			if (fd == -1)
			{
				error_string(cmds->in_file->args[i]);
				pipex->status[0] = FILE_ERROR;
				return;
			}
			i++;
			if (i != cmds->in_file->args_count)
				close(fd);
			else
			{
				*infile_fd = fd;
				pipex->status[0] = FILE_VALID;
			}
		}
	}
}

void	last_close(t_object *pipex)
{
	if (pipex->infile_fd != -1)
		close(pipex->infile_fd);
	if (pipex->outfile_fd != -1)
		close(pipex->outfile_fd);
	if (pipex->num_commands > 1)
	{
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		close(pipex->prev_pipe_in);
	}
}

void	fire_up_pipeinator(t_object *pipex, t_cmd *cmds)
{
	pipex->last_child_pid = -1;
	pipex->num_commands = cmds->cmds_count;
	pipex->prev_pipe_in = pipex->infile_fd;
	pipex->last_status = 0;
}

//MOVE FROM HERE
char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	write(fd, s, len);
}

char	*ft_strcpy(char *dest, char *src)
{
	char	*dest_cpy;

	dest_cpy = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest_cpy);
}
