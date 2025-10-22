/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:50:32 by cdohanic          #+#    #+#             */
/*   Updated: 2025/09/22 09:47:14 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ensure_arg_capacity(t_simple_cmd *cmd)
{
	void	*tmp;

	if (cmd->args_count < cmd->args_capacity - 1)
		return (0);
	tmp = ft_realloc(cmd->args, sizeof(char *) * cmd->args_capacity,
			sizeof(char *) * cmd->args_capacity * 2);
	if (!tmp)
		return (-1);
	cmd->args_capacity *= 2;
	cmd->args = tmp;
	return (0);
}

int	parse_word(char *word, t_simple_cmd **current_cmd)
{
	t_simple_cmd	*cmd;

	if (word == NULL)
		return (-1);
	cmd = *current_cmd;
	if (ensure_arg_capacity(cmd) == -1)
		return (-1);
	cmd->args[cmd->args_count] = ft_strdup(word);
	if (cmd->args[cmd->args_count] == NULL)
		return (-1);
	cmd->args_count++;
	cmd->args[cmd->args_count] = NULL;
	return (0);
}
