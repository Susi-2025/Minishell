/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:07:22 by cdohanic          #+#    #+#             */
/*   Updated: 2025/07/03 12:28:19 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

typedef struct s_object
{
	int		pipefd[2];
	int		prev_pipe_in;
	int		last_child_pid;
	pid_t	pid;
	int		infile_fd;
	int		outfile_fd;
	char	**cmd;
	int		status;
	int		num_commands;
	int		last_status;
}	t_object;

char	**ft_split(char const *str, char c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcat(char *dest, char *src);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strcpy(char *dest, char *src);
void	free_strings(char **str);
void	error_string(char *argv);
void	failed_exec(char *argv);
char	**cmd_error(char *argv);
int		path_exists(char *env[]);
char	*correct_path(char *env[], char *cmd);
char	**parse_cmd(char *argv, char *env[]);
void	fd_init(int *infile_fd, int *outfile_fd, char *in, char *out);
void	last_close(t_object *pipex);
void	fire_up_pipeinator(t_object *pipex, int argc);
void	run_cmd(t_object *pipex, int i, char *argv[], char *env[]);
void	reading_pipe(t_object *pipex, int i);
void	writing_pipe(t_object *pipex, int i);
void	child_process(t_object *pipex, int i, char *argv[], char *env[]);
void	parent_process(t_object *pipex, int i);
#endif
