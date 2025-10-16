/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:54:37 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/16 14:54:57 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "heredoc.h"
// heredoc
int		heredoc(t_cmd *cmds, char **env[], char **args, int args_count);
int		join_and_free(char **output, char *input);
void	init_pipe_heredoc(t_pipe_simple *pipex);
int		open_pipe_heredoc(t_pipe_simple *pipex);
void	connect_pipe_heredoc(t_pipe_simple *pipex);
#endif
