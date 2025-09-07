/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:27:14 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/07 16:45:30 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "structs.h"

// command
int	init_envp(t_cmd *cmds, char **envp);
int	exec_command(t_cmd *shell);
//int	exec_command(t_cmd *cmds, char **envp);
int exec_built_in(t_cmd *shell);
int	exec_export_only(t_cmd *shell);
int exec_echo(t_cmd *shell);
int exec_cd(t_cmd *shell);

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
int error_msg(t_cmd *shell, int code, char *str);

#endif
