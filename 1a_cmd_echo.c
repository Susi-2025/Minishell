/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_cmd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/18 10:51:25 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	echo_stored_var(char **envp, char *string);

int exec_echo(t_shell *shell)
{
	int	i;
		
	if (!shell)
		return(error_msg(shell, 1, "shell"));
	i = 1;
	while(shell->cmd_args[i])
	{
		if(shell->cmd_args[i][0] == '$')
			echo_stored_var(shell->envp, &(shell->cmd_args[i][1]));
		else
			printf("%s", shell->cmd_args[i]);
		if (i < (ft_len_2d(shell->cmd_args) - 1))
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}

static	void	echo_stored_var(char **envp, char *string)
{
	char	*temp;
	char	*sub_temp;
	
	temp = find_var(envp, string);
	if (temp != NULL)
	{
		sub_temp = ft_strchr(temp, '=');
		if (sub_temp && (sub_temp + 1))
			printf("%s", sub_temp + 1);
	}
}