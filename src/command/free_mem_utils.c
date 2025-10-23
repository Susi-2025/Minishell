/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:34:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/23 16:00:13 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_2_mem(char *old_wd, char *next_wd, int exit_code)
{
	if (old_wd)
		free(old_wd);
	if (next_wd)
		free(next_wd);
	return (exit_code);
}

void	free_and_exit(t_cmd *cmds, char **temp_env, int status)
{
	if (cmds->orig_stdin >= 2)
		close(cmds->orig_stdin);
	if (cmds->orig_stdout >= 2)
		close(cmds->orig_stdout);
	if (cmds)
		free_cmd(cmds);
	if (temp_env)
		ft_free_triptr(&temp_env);
	exit((unsigned char)status);
}

//set to >= 0 for cover cases:
/*
Prompt: asdfasfd ?asdfasdf >sdfads <asfdasd
bash: asfdasd: No such file or directory
==3046173== 
==3046173== FILE DESCRIPTORS: 4 open (3 std) at exit.
==3046173== Open file descriptor 3: sdfads
==3046173==    at 0x49D95AB: open (open64.c:41)
==3046173==    by 0x4054C1: open_redir_file (in /home/vinguyen/Documents/Minishell/minishell)
==3046173==    by 0x405408: open_all_redirections (in /home/vinguyen/Documents/Minishell/minishell)
==3046173==    by 0x4052A5: handle_io_redirection (in /home/vinguyen/Documents/Minishell/minishell)
==3046173==    by 0x404BC5: child_process (in /home/vinguyen/Documents/Minishell/minishell)
==3046173==    by 0x404842: pipe_and_fork_logic (in /home/vinguyen/Documents/Minishell/minishell)
==3046173==    by 0x404A00: ft_pipex (in /home/vinguyen/Documents/Minishell/minishell)
==3046173==    by 0x40151B: run_line (in /home/vinguyen/Documents/Minishell/minishell)
==3046173==    by 0x401458: main (in /home/vinguyen/Documents/Minishell/minishell)

*/