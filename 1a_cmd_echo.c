/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_cmd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/18 13:55:18 by vinguyen         ###   ########.fr       */
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
	while(shell->cmd_args[i])
	{
		if(shell->cmd_args[i][0] == '$')
		{
			temp = find_var(shell->envp, &(shell->cmd_args[i][1]));
			if (temp != NULL)
				printf("%s", temp);
		}
		else
			printf("%s", shell->cmd_args[i]);
		if (i < (ft_len_2d(shell->cmd_args) - 1))
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}