/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:56:39 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/23 12:04:26 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_no_file(t_cmd *cmds, char *arg, char *env[], int exit_code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_and_exit(cmds, env, exit_code);
}

void	handle_cmd_error(t_cmd *cmds, char *arg, char *env[], int exit_code)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_and_exit(cmds, env, exit_code);
}
