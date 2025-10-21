/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:02:33 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/21 11:53:32 by vinguyen         ###   ########.fr       */
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

int	error_cmd(int code, char *str_cmd, char *arg, char *message)
{
	printf("%s: ", str_cmd);
	printf("%s: ", arg);
	printf("%s\n", message);
	return (code);
}

int	error_cmd_fd(int code, char *str_cmd, char *arg, char *message)
{
	ft_printf_fd(2, "%s: ", str_cmd);
	ft_printf_fd(2, "%s: ", arg);
	ft_printf_fd(2, "%s\n", message);
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
	return (code);
}

int	error_string_cd_1(char *argv, int code)
{
	char	error[1000];

	ft_strcpy(error, "bash: ");
	ft_strcat(error, "cd: ");
	ft_strcat(error, argv);
	ft_strcat(error, "\n");
	ft_putstr_fd(error, 2);
	return (code);
}

int	error_string_cd_2(char *argv, int code)
{
	char	error[1000];

	ft_strcpy(error, "bash: ");
	ft_strcat(error, "cd: ");
	ft_strcat(error, argv);
	ft_strcat(error, " : No such file or directory\n");
	ft_putstr_fd(error, 2);
	return (code);
}
