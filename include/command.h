/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:27:14 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/08 18:50:58 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "structs.h"

// command
int	init_envp(t_cmd *cmds, char **envp);
int	execution_single(t_cmd *cmds, char **temp_env);

int	check_built_in(char *cmd);
int exec_built_in(t_cmd *shell, char **args, char **temp_env, int args_count);
int	exec_export_only(t_cmd *shell);
int exec_echo(t_cmd *shell, char **args, int args_count);
int exec_cd(t_cmd *shell, char **args);

int exec_external(t_cmd *cmds, char **args, char **temp_env);

// int	exec_unset(t_cmd *shell);
// int	exec_env(t_cmd *shell);
// int	exec_pwd(t_cmd *shell);

// command utilities
char	*find_var(char **envp, char *str);
void	sort_2d_array(char **strs);
int	ft_len_2d(char **strs);
int ft_is_numeric(char *s);
int	update_env(t_cmd *shell, char *key, char *value);
int	reduce_env(t_cmd *shell, char *str);

void	cmd_print(t_cmd *cmds);

// handle_error
//void	free_shell(t_cmd *shell);
int	error_malloc(t_cmd *shell, int code);
//int error_msg(t_cmd *shell, int code, char *str);
int error_msg(int code, char *str);

#endif
