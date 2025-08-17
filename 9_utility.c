/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_utility.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:02:33 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/17 18:20:29 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_malloc(t_shell *shell, int code)
{
	free_shell(shell);
	return (code);
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->cmd_args)
		ft_free_triptr(&(shell->cmd_args));
	if (shell->envp)
		ft_free_triptr(&(shell->envp));
}

int error_msg(t_shell *shell, int code, char *str)
{
	printf("%s\n", str);
	free_shell(shell);
	return (code);
}