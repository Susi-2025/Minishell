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
#include "minishell.h"

void	fd_init(int *infile_fd, int *outfile_fd, char *in, char *out)
{
	if (out != NULL)
	{
		*outfile_fd = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*outfile_fd == -1)
			error_string(out);
	}
	if (in != NULL)
	{	
		*infile_fd = open(in, O_RDONLY);
		if (*infile_fd == -1)
			error_string(in);
	}
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