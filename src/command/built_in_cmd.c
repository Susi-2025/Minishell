/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/21 19:30:07 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	exec_pwd(t_cmd *cmds);
static	int	exec_unset(t_cmd *cmds, char **args, char ***temp_env);
static	int	exec_exit(t_cmd *cmds, char *s, char **temp_env, int args_count);

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

static	int	exec_pwd(t_cmd *cmds)
{
	char	*out;

	out = find_var(cmds->envp, "PWD=");
	if (out)
		ft_printf_fd(1, "%s\n", out);
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
		return (error_cmd(127, "env", arg, NO_SUCH_FILE ));
	//int	error_env(int code, char *str_cmd, char *arg, char *message)
	i = 0;
	len = ft_len_2d(cmds->envp);
	while (i < len)
	{
		if (ft_strchr(cmds->envp[i], '=') && cmds->envp[i])
			ft_printf_fd(1, "%s\n", cmds->envp[i]);
		i++;
	}
	return (0);
}

static	int	exec_unset(t_cmd *cmds, char **args, char ***temp_env)
{
	// if (!temp_env || !args[1])
	if (!temp_env)
	{
		ft_printf_fd(2, "Error:\n");
		return (1);
	}
	else if (!args[1])
		return (1);
	else
	{
		// printf("Execute unset\n");
		return (reduce_env(cmds, args[1], temp_env));
	}
}

static	int	exec_exit(t_cmd *cmds, char *s, char **temp_env, int args_count)
{
	int	status;

	if (args_count > 2)
	{
		if (ft_is_numeric(s) == 0)
		{
			ft_printf_fd(2, "exit\n");
			status = error_cmd_fd(2, "exit", s, NUM_ARG); // will exit
			free_and_exit(cmds, temp_env, status);
		}
		else
			return(error_cmd_fd(1, "bash", "exit", MANY_ARGS)); // no exit
	}
	else
	{
		ft_printf_fd(2, "exit\n");
		if (s && ft_is_numeric(s))
			status = ft_atoi(s);
		else if (s)
			status = error_cmd_fd(2, "exit", s, NUM_ARG);
		else
			status = 0;
		free_and_exit(cmds, temp_env, status);
	}
	return (status);
}