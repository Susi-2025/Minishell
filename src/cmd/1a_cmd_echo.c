/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_cmd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/08 11:31:15 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_echo(t_cmd *cmds)
{
	int	i;
	//char	*temp;
		
	if (!cmds)
		//return(error_msg(cmds, 1, "cmds"));
		return(error_msg(1, "cmds"));
	i = 1;
	while(cmds->simple_cmds[0]->args[i])
	{
		printf("%s", cmds->simple_cmds[0]->args[i]);
		if (i < (cmds->simple_cmds[0]->args_count - 1))
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}