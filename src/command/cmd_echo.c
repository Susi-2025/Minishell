/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/21 10:24:20 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_echo(t_cmd *cmds, char **args, int args_count)
{
	int	i;
	int	no_new_line;

	if (!cmds)
		return (error_msg(1, "cmds"));
	i = 1;
	no_new_line = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "-n") == 0)
			no_new_line = 1;
		else
			printf("%s", args[i]);
		if (i < (args_count - 1))
			printf(" ");
		i++;
	}
	if (no_new_line == 0)
		printf("\n");
	return (0);
}
