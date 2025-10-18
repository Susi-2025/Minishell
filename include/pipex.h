/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:07:22 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/15 15:01:08 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>

# include "structs.h"

typedef enum s_status {
    FILE_NONE = 0,      // no infile
    FILE_ERROR = -1,    // open failed
    FILE_VALID = 1      // valid fd
} t_status;

typedef struct s_object
{
	int		pipefd[2];
	int		prev_pipe_in;
	int		last_child_pid;
	pid_t	pid;
	int		infile_fd;
	int		outfile_fd;
	int		file_flags[2];
	char	**cmd;
	// int		status;
	int		num_commands;
	int		last_status;
	t_status status;
}	t_object;

// viet add for here_doc
typedef struct s_pipe
{
	int		pipefd[2];
	pid_t	pid;
	int		infile_fd;
	int		outfile_fd;
}	t_pipe_simple;

/* Main function*/
int		ft_pipex(t_cmd *cmds, char **env[]); //add for updating env ability

/* String utils*/
char	*ft_strcat(char *dest, char *src);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strcpy(char *dest, char *src);

/* Memory and error*/
void	free_strings(char **str);
void	error_string(char *argv);
void	error_string_export(char *argv);
void	failed_exec(char *argv);
char	**cmd_error(char *argv);
void	error_syntax(char *argv);

int		path_exists(char *env[]);
char	*correct_path(char *cmd, char *env[]);
// char	**parse_cmd(char *argv, char *env[]);
void	fd_init(int *infile_fd, int *outfile_fd, t_object *pipex, t_simple_cmd *cmds);
void	last_close(t_object *pipex);
void	fire_up_pipeinator(t_object *pipex, t_cmd *cmds);
void	run_cmd(t_object *pipex, int i, t_cmd *cmds, char *env[]);
void	child_process(t_object *pipex, int i, t_cmd *cmds, char *env[]);
void	parent_process(t_object *pipex, int i);
#endif
