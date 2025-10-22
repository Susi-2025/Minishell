/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:29:14 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/22 17:27:14 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	pipex->prev_pipe_in = pipex->infile_fd;
	pipex->last_status = 0;
	pipex->status = FILE_NONE;
}

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
