/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:27:14 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/21 15:32:46 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "structs.h"

# define NUM_ARG "numeric argument required"
# define MANY_ARGS "too many arguments"
# define NO_SUCH_FILE "No such file or directory"
# define ERR_EMPTY_FOLDER "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory"
// command
int		exec_parent(t_cmd *cmds, char **args, char **env[], int args_count);
int		init_envp(t_cmd *cmds, char **envp);
int		check_built_in(char *cmd);
int		exec_built_in(t_cmd *shell, char **args,
			char ***temp_env, int args_count);
int		exec_export(t_cmd *cmds, char **args, char ***temp_env);
int		exec_export_only(t_cmd *shell);
int		export_with_args(t_cmd *cmds, char *arg_str, char ***temp_env);
int		exec_echo(t_cmd *shell, char **args, int args_count);
int		exec_cd(t_cmd *shell, char **args);
int		exec_env(t_cmd *cmds);

// command utilities
int		ft_len_2d(char **strs);
int		ft_is_numeric(char *s);
int		update_env(t_cmd *shell, char *key, char *value);
int		reduce_env(t_cmd *cmds, char *str, char ***env);
int		insert_env(t_cmd *cmds, char *str, char ***temp_env);
void	envp_print(char **envp);
void	cmd_print(t_cmd *cmds);

char	*find_var(char **envp, char *str);
int		check_var_env(char **envp, char *str);
void	sort_2d_array(char **strs);
// string utilities
int		invalid_args(char *str);
char	*ft_strhead(char *str, char c);
char	*ft_strtail(char *str, char c);
void	ft_copy_str(char *origin, char *key, char *value);
char	*create_new_str(char *key, char *value);

void	printf_for_export(char *str);
// handle_error
int		error_malloc(t_cmd *shell, int code);
int		error_msg(int code, char *str);
int		error_string_cd(char *argv, int code);
int		error_string_cd_1(char *argv, int code);
int		error_string_cd_2(char *argv, int code);
int		error_cmd(int code, char *str_cmd, char *arg, char *message);
int		error_cmd_fd(int code, char *str_cmd, char *arg, char *message);
// free_mem
int		free_2_mem(char *old_wd, char *next_wd, int exit_code);
void	free_and_exit(t_cmd *cmds, char **temp_env, int status);
#endif
