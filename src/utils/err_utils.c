/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:02:33 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/23 07:54:54 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_malloc(t_cmd *cmds, int code)
{
	free_cmd(cmds);
	return (code);
}

int	error_msg(int code, char *str)
{
	ft_printf_fd(2, "%s\n", str);
	return (code);
}

int	error_cmd_fd(int code, char *str_cmd, char *arg, char *message)
{
	ft_printf_fd(2, "bash: ");
	ft_printf_fd(2, "%s: ", str_cmd);
	if (arg[0] != '\0')
		ft_printf_fd(2, "%s: ", arg);
	ft_printf_fd(2, "%s\n", message);
	return (code);
}

int	error_cmd_fd_no_bash(int code, char *str_cmd, char *arg, char *message)
{
	ft_printf_fd(2, "%s: ", str_cmd);
	if (arg[0] != '\0')
		ft_printf_fd(2, "%s: ", arg);
	ft_printf_fd(2, "%s\n", message);
	return (code);
}
