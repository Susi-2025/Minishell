/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:27:14 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/17 18:19:14 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h> 
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include "./libft/libft.h"
/*
typedef struct s_stack
{
	int		pipefd[2];
	pid_t	pid[2];
	int		fd[2];
}	t_stack;
*/
typedef struct s_stack
{
	char	**cmd_args;
	char	**envp;
		
}	t_shell;
/*
void	first_child_run(t_stack *pipex, char **av, char **envp);
void	second_child_run(t_stack *pipex, char **av, char **envp);
void	run_command(t_stack *pipex, char *command, char **envp);
char	*get_path(char **envp, char *cmd);

void	err_exit(char *msg, int exit_code);
void	err_fork_dup2(t_stack *pipex, char *msg, int exit_code);
void	err_open_file(t_stack *pipex, char *av, int exit_code);
void	print_error(char *str, char *msg);

void	handle_no_file(t_stack *pipex, char **cmd_argvs);
void	handle_envp_error(t_stack *pipex, char **cmd_argvs, int exit_code);
void	handle_command_error(t_stack *pipex, int exit_code);
void	handle_cmd_path_err(t_stack *pipex, char *msg, int exit_code);
void	handle_exec_error(t_stack *pipex, char *cmd_path, char **cmd_argvs);
void	close_stack(t_stack *pipex);
*/
// command
int	exec_command(t_shell *shell);
int exec_built_in(t_shell *shell);
int	exec_export_only(t_shell *shell);

// command utilities
char	*find_var(char **envp, char *str);
void	sort_2d_array(char **strs);
int	ft_len_2d(char **strs);

// handle_error
void	free_shell(t_shell *shell);
int	error_malloc(t_shell *shell, int code);
int error_msg(t_shell *shell, int code, char *str);

#endif
