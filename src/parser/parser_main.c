/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:27:52 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/22 21:49:59 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ensure_cmds_capacity(t_cmd *cmds)
{
	void	*tmp;

	if (cmds->cmds_count < cmds->cmds_capacity)
		return (0);
	tmp = ft_realloc(cmds->simple_cmds, sizeof(t_simple_cmd *)
			* cmds->cmds_capacity, sizeof(t_simple_cmd *) * cmds->cmds_capacity
			* 2);
	if (!tmp)
		return (-1);
	cmds->simple_cmds = tmp;
	cmds->cmds_capacity *= 2;
	return (0);
}

static t_simple_cmd	*init_simple_cmd(void)
{
	t_simple_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_simple_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args_capacity = 4;
	new_cmd->args_count = 0;
	new_cmd->args = malloc(sizeof(char *) * new_cmd->args_capacity);
	if (!new_cmd->args)
	{
		free(new_cmd);
		return (NULL);
	}
	new_cmd->args[0] = NULL;
	new_cmd->redirections = NULL;
	return (new_cmd);
}

int	create_current_cmd(t_simple_cmd **current_cmd, t_cmd *cmds)
{
	if (ensure_cmds_capacity(cmds) == -1)
		return (-1);
	*current_cmd = init_simple_cmd();
	if (!*current_cmd)
		return (-1);
	cmds->simple_cmds[cmds->cmds_count] = *current_cmd;
	cmds->cmds_count++;
	return (0);
}

static int	cmd_init(t_cmd *cmds, char *env[])
{
	cmds->cmds_capacity = 2;
	cmds->cmds_count = 0;
	cmds->heredoc_idx = 0;
	cmds->envp = env;
	cmds->err_file = NULL;
	cmds->file_append = NULL;
	cmds->simple_cmds = malloc(sizeof(t_simple_cmd *) * cmds->cmds_capacity);
	if (!cmds->simple_cmds)
		return (-1);
	return (0);
}

int	parse_tokens(t_cmd *cmds, t_token *tokens, int token_count, char *env[])
{
	int				i;
	t_simple_cmd	*current_cmd;

	if (cmd_init(cmds, env) == -1)
		return (ERROR);
	current_cmd = NULL;
	i = 0;
	while (i < token_count && tokens[i].type != TOKEN_EOF)
	{
		if (!current_cmd)
		{
			if (create_current_cmd(&current_cmd, cmds) == -1)
				return (ERROR);
		}
		if (process_word(&tokens[i], &current_cmd, env, cmds->err_code) == -1)
			return (ERROR);
		if (handle_redirection(tokens, token_count, &i, cmds) == -1)
			return (ERROR);
		if (tokens[i].type == PIPE)
			current_cmd = NULL;
		i++;
	}
	return (SUCCESS);
}
