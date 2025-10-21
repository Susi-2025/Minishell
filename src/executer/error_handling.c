/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:46:00 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/15 14:57:18 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strings(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*error_redir(char *argv)
{
	ft_putstr_fd("bash: $", 2);
	ft_putstr_fd(argv, 2);
    ft_putstr_fd(": ambiguous redirect", 2);
    ft_putstr_fd("'\n", 2);
	return (NULL);
}

void	error_string(char *argv)
{
	char	error[1000];

	ft_strcpy(error, "bash: ");
	ft_strcat(error, argv);
	ft_strcat(error, ": ");
	ft_strcat(error, strerror(errno));
	ft_strcat(error, "\n");
	ft_putstr_fd(error, 2);
}

void error_syntax(char *argv)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    ft_putstr_fd(argv, 2);
    ft_putstr_fd("'\n", 2);
}

void	error_string_export(char *argv)
{
	char	error[1000];

	ft_strcpy(error, "bash: ");
	ft_strcat(error, "export ");
	ft_strcat(error, argv);
	ft_strcat(error, ": ");
	ft_strcat(error, "not a valid identifier");
	ft_strcat(error, "\n");
	ft_putstr_fd(error, 2);
}

void	failed_exec(char *argv)
{
	char	error[1000];

	ft_strcpy(error, "");
	ft_strcat(error, argv);
	ft_strcat(error, ": ");
	ft_strcat(error, "command not found");
	ft_strcat(error, "\n");
	ft_putstr_fd(error, 2);
}

char	**cmd_error(char *argv)
{
	char	**cmd;
	int		i;	

	cmd = ft_split(argv, ' ');
	if (!cmd)
		return (NULL);
	i = 1;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	cmd[1] = NULL;
	return (cmd);
}

int	path_exists(char *env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (1);
		i++;
	}
	return (0);
}
