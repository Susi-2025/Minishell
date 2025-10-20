/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_print_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:54:00 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/20 13:57:43 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	simple_cmd_print(t_simple_cmd *simple_cmd);

void	cmd_print(t_cmd *cmds)
{
	int				i;
	t_simple_cmd	*cmd;

	printf("Print cmds\n");
	printf("Value of cmds_capacity: %d\n", cmds->cmds_capacity);
	printf("Value of cmds_count: %d\n", cmds->cmds_count);
	i = 0;
	while (i < cmds->cmds_count && cmds->simple_cmds && cmds->simple_cmds[i])
	{
		cmd = cmds->simple_cmds[i];
		if (cmd->out_file != NULL)
		{
			for (int i = 0; i < cmd->out_file->args_count; i++)
				printf("Value of out_file: %s\n", cmd->out_file->args[i]);
		}
		if (cmd->in_file != NULL)
		{
			for (int i = 0; i < cmd->in_file->args_count; i++)
				printf("Value of in_file: %s\n", cmd->in_file->args[i]);
		}
		i++;
	}
	i = 0;
	while (i < cmds->cmds_count && cmds->simple_cmds && cmds->simple_cmds[i])
	{
		printf("Simple command %d\n", i);
		simple_cmd_print(cmds->simple_cmds[i]);
		i++;
	}
	// printf("Print envp\n");
	if (!(cmds->envp && cmds->envp[0]))
		envp_print(cmds->envp);
	// else
	// 	printf("ENV is NULL\n");
}

static	void	simple_cmd_print(t_simple_cmd *simple_cmd)
{
	int	i;

	if (!simple_cmd)
	{
		printf("simple cmd is NULL\n");
		return ;
	}
	printf("Value of args_capacity: %d\n", simple_cmd->args_capacity);
	printf("Value of args_count: %d\n", simple_cmd->args_count);
	i = 0;
	while (i < simple_cmd->args_count)
	{
		printf("Value of args at %d position is: %s\n", i, simple_cmd->args[i]);
		i++;
	}
}

void	envp_print(char **envp)
{
	int	i;
	int	len;

	if (!envp)
	{
		printf("envp is NULL\n");
		return ;
	}
	i = 0;
	len = ft_len_2d(envp);
	while (i < len)
	{
		printf("Value of envp at %d position is: %s\n", i, envp[i]);
		i++;
	}
}
