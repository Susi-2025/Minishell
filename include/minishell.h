/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:27:14 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/19 13:42:08 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h> 
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include "../libft/libft.h"
/*
typedef struct s_stack
{
	int		pipefd[2];
	pid_t	pid[2];
	int		fd[2];
}	t_stack;
*/
typedef struct s_simple_cmd
{
	int     args_capacity;
	int     args_count;
	char    **args;
} t_simple_cmd;

typedef struct s_stack
{
	int cmds_capacity;
	int cmds_count;
	t_simple_cmd **simple_cmds;
	char	*out_file;
	char	*in_file;
	char	*err_file;
	char	*here_doc;
	char	*file_append;
	char	**envp; //vietadd		
}	t_shell; //change the name from t_cmd to t_shell;

// command
int	exec_command(t_shell *shell);
int exec_built_in(t_shell *shell);
int	exec_export_only(t_shell *shell);
int exec_echo(t_shell *shell);
int exec_cd(t_shell *shell);

// int	exec_env(t_shell *shell);
// int	exec_pwd(t_shell *shell);

// command utilities
char	*find_var(char **envp, char *str);
void	sort_2d_array(char **strs);
int	ft_len_2d(char **strs);
int	update_env(t_shell *shell, char *key, char *value);

// handle_error
void	free_shell(t_shell *shell);
int	error_malloc(t_shell *shell, int code);
int error_msg(t_shell *shell, int code, char *str);

#endif
