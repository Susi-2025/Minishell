/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:50:32 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/24 16:51:41 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	create_current_cmd(t_simple_cmd **current_cmd, t_cmd *cmds)
{
	void	*tmp;

	if (cmds->cmds_count >= cmds->cmds_capacity)
	{
		tmp = realloc(cmds->simple_cmds,
				sizeof(t_simple_cmd) * cmds->cmds_capacity * 2);
		if (!tmp)
			return (-1);
		cmds->simple_cmds = tmp;
		cmds->cmds_capacity *= 2;
	}
	*current_cmd = malloc(sizeof(t_simple_cmd));
	if (!*current_cmd)
		return (-1);
	(*current_cmd)->args_capacity = 4;
	(*current_cmd)->args_count = 0;
	(*current_cmd)->args = malloc(sizeof(char *)
			* (*current_cmd)->args_capacity);
	if (!(*current_cmd)->args)
		return (free(*current_cmd), -1);
	cmds->simple_cmds[cmds->cmds_count] = *current_cmd;
	cmds->cmds_count++;
	return (0);
}

int	parse_word(char *word, t_simple_cmd **current_cmd, t_cmd *cmds)
{
	void	*tmp;

	if (word == NULL)
		return (-1);
	if (!*current_cmd)
	{
		if (create_current_cmd(current_cmd, cmds) == -1)
			return (-1);
	}
	if ((*current_cmd)->args_count >= (*current_cmd)->args_capacity - 1)
	{
		tmp = realloc((*current_cmd)->args, sizeof(char *)
				* (*current_cmd)->args_capacity * 2);
		if (!tmp)
			return (-1);
		(*current_cmd)->args_capacity *= 2;
		(*current_cmd)->args = tmp;
	}
	(*current_cmd)->args[(*current_cmd)->args_count] = ft_strdup(word);
	if ((*current_cmd)->args[(*current_cmd)->args_count] == NULL)
		return (-1);
	(*current_cmd)->args_count++;
	(*current_cmd)->args[(*current_cmd)->args_count] = NULL;
	return (0);
}
