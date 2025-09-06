/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:28:21 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/17 19:28:22 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmds)
{
	int	i;
	int	j;

	if (!cmds)
		return ;
	i = 0;
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
			free(cmds->simple_cmds[i]->args);
			free(cmds->simple_cmds[i]);
		}
		i++;
	}
    free(cmds->simple_cmds);
    free(cmds->in_file);
    free(cmds->out_file);
    free(cmds->err_file);
    free(cmds->here_doc);
    free(cmds->file_append);
    free(cmds);
}

void	free_tokens(t_token *tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}