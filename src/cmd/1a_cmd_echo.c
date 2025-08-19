/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_cmd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/19 13:43:04 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_echo(t_shell *shell)
{
	int	i;
	char	*temp;
		
	if (!shell)
		return(error_msg(shell, 1, "shell"));
	i = 1;
	while(shell->simple_cmds[0]->args[i])
	{
		if(shell->simple_cmds[0]->args[i][0] == '$')
		{
			temp = find_var(shell->envp, &(shell->simple_cmds[0]->args[i][1]));// cristian already handle this in the parsing
			if (temp != NULL)
				printf("%s", temp);
		}
		else
			printf("%s", shell->simple_cmds[0]->args[i]);
		if (i < (ft_len_2d(shell->simple_cmds[0]->args) - 1))
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}