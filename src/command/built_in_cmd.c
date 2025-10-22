/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/22 22:34:22 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	int	exec_pwd(t_cmd *cmds);
static	int	exec_unset(t_cmd *cmds, char **args, char ***temp_env);

int	exec_built_in(t_cmd *cmds, char **args, char ***temp_env, int args_count)
{
	if (!cmds || !cmds->simple_cmds || !args[0])
		return (error_msg(1, "cmds"));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (exec_pwd(cmds));
	else if (ft_strcmp(args[0], "env") == 0)
		return (exec_env(cmds, args[1], args_count));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (exec_echo(cmds, args, args_count));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (exec_cd(cmds, args));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (exec_exit(cmds, args[1], *temp_env, args_count));
	else if (ft_strcmp(args[0], "export") == 0)
		return (exec_export(cmds, args, temp_env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (exec_unset(cmds, args, temp_env));
	return (0);
}

int	exec_pwd(t_cmd *cmds)
{
	char	*out;

	out = find_var(cmds->envp, "PWD=");
	if (out)
		printf("%s\n", out);
	else
		return (error_msg(1, "pwd"));
	return (0);
}

int	exec_env(t_cmd *cmds, char *arg, int args_count)
{
	int	i;
	int	len;

	if (!cmds->envp)
		return (error_msg(1, "envp"));
	if (args_count != 1)
		return (error_cmd_fd(127, "env", arg, NO_SUCH_FILE));
	i = 0;
	len = ft_len_2d(cmds->envp);
	while (i < len)
	{
		if (ft_strchr(cmds->envp[i], '=') && cmds->envp[i])
			printf("%s\n", cmds->envp[i]);
		i++;
	}
	return (0);
}

static	int	exec_unset(t_cmd *cmds, char **args, char ***temp_env)
{
	if (!temp_env)
	{
		printf("Error:\n");
		return (1);
	}
	else if (!args[1])
		return (0);
	else
		return (reduce_env(cmds, args[1], temp_env));
}
