/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_err_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:02:33 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/16 12:18:04 by vinguyen         ###   ########.fr       */
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
	printf("%s\n", str);
	return (code);
}

int	error_string_cd(char *argv, int code)
{
	char	error[1000];

	ft_strcpy(error, "bash: ");
	ft_strcat(error, "cd: ");
	ft_strcat(error, argv);
	ft_strcat(error, " not set\n");
	ft_putstr_fd(error, 2);
	return  (code);
}