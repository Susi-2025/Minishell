/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_cmd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/07 10:28:31 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_echo(t_cmd *cmds)
{
	int	i;
	char	*temp;
		
	if (!cmds)
		return(error_msg(cmds, 1, "cmds"));
	i = 1;
	while(cmds->simple_cmds[0]->args[i])
	{
		if(cmds->simple_cmds[0]->args[i][0] == '$')
		{
			temp = find_var(cmds->envp, &(cmds->simple_cmds[0]->args[i][1]));// cristian already handle this in the parsing
			if (temp != NULL)
				printf("%s", temp);
		}
		else
			printf("%s", cmds->simple_cmds[0]->args[i]);
		if (i < (ft_len_2d(cmds->simple_cmds[0]->args) - 1))
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}