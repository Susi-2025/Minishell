/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:27:14 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/09 12:02:05 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "structs.h"
// command
int		init_envp(t_cmd *cmds, char **envp);
int		execution_single(t_cmd *cmds, char **temp_env);
int		check_built_in(char *cmd);
int		exec_built_in(t_cmd *shell, char **args,
			char **temp_env, int args_count);
int		exec_export_only(t_cmd *shell);
int		exec_echo(t_cmd *shell, char **args, int args_count);
int		exec_cd(t_cmd *shell, char **args);
int		exec_external(t_cmd *cmds, char **args, char **temp_env);

// command utilities
int		ft_len_2d(char **strs);
int		ft_is_numeric(char *s);
int		update_env(t_cmd *shell, char *key, char *value);
int		reduce_env(t_cmd *shell, char *str);
void	envp_print(char **envp);
void	cmd_print(t_cmd *cmds);
char	*find_var(char **envp, char *str);
void	sort_2d_array(char **strs);

// handle_error
int		error_malloc(t_cmd *shell, int code);
int		error_msg(int code, char *str);
#endif
