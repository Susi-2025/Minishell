/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:59:25 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/22 21:49:45 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	free_simple_cmds(t_cmd *cmds);

void	free_cmd(t_cmd *cmds)
{
	if (!cmds)
		return ;
	if (cmds->simple_cmds)
		free_simple_cmds(cmds);
	if (cmds->heredoc_files)
		vector_destroy_heredocs(cmds->heredoc_files);
	free(cmds->simple_cmds);
	free(cmds->err_file);
	free(cmds->file_append);
	free(cmds);
	cmds = NULL;
}

static	void	free_simple_cmds(t_cmd *cmds)
{
	int	i;
	int	j;

	i = 0;
	if (!cmds)
		return ;
	while (i < cmds->cmds_count)
	{
		if (cmds->simple_cmds[i])
		{
			j = 0;
			while (j < cmds->simple_cmds[i]->args_count)
			{
				free(cmds->simple_cmds[i]->args[j]);
				j++;
			}
			vector_destroy(cmds->simple_cmds[i]->redirections);
			free(cmds->simple_cmds[i]->args);
			free(cmds->simple_cmds[i]);
		}
		i++;
	}
}
