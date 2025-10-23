/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:45:39 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/23 10:33:44 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_exit_code(char *s);

int	exec_exit(t_cmd *cmds, char *s, char **temp_env, int args_count)
{
	int	status;

	status = cmds->err_code;
	if (args_count > 2)
	{
		if (ft_is_numeric(s) == 0)
		{
			printf("exit\n");
			status = error_cmd_fd(2, "exit", s, NUM_ARG);
			free_and_exit(cmds, temp_env, status);
		}
		else
			return (error_cmd_fd(1, "exit", "", MANY_ARGS));
	}
	else
	{
		printf("exit\n");
		status = set_exit_code(s);
		free_and_exit(cmds, temp_env, status);
	}
	return (status);
}

static int	set_exit_code(char *s)
{
	int	status;

	if (s && ft_is_numeric(s))
		status = ft_atoi(s);
	else if (s)
		status = error_cmd_fd(2, "exit", s, NUM_ARG);
	else
		status = 0;
	return (status);
}
