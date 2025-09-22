/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:27:14 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/22 11:42:29 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "structs.h"
// command
void	exec_parent(t_cmd *cmds, char **args, char **env[], int args_count);
int		init_envp(t_cmd *cmds, char **envp);
int		check_built_in(char *cmd);
int		exec_built_in(t_cmd *shell, char **args,
			char ***temp_env, int args_count);
int		exec_export(t_cmd *cmds, char **args, char ***temp_env);
int		exec_export_only(t_cmd *shell);
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
void	sort_2d_array(char **strs);
// handle_error
int		error_malloc(t_cmd *shell, int code);
int		error_msg(int code, char *str);
// heredoc
int		heredoc_exec(t_cmd *cmds, char **env[], char **args, int args_count);
#endif
