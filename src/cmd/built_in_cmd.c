/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/09 17:06:34 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	exec_pwd(t_cmd *cmds);
// static	int	exec_env(t_cmd *cmds);
static	int	exec_unset(t_cmd *cmds, char **args, char ***temp_env);
// static	int	exec_unset(char **args, char ***temp_env);
static	void	exec_exit(t_cmd *cmds, char *s, char **temp_env);


int exec_built_in(t_cmd *cmds, char **args, char ***temp_env, int args_count)
{
	//printf("Exec built-in\n");
	if (!cmds || !cmds->simple_cmds || !args[0])
		//return(error_msg(cmds, 1, "cmds"));
		return(error_msg(1, "cmds"));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (exec_pwd(cmds));
	else if (ft_strcmp(args[0], "env") == 0)
		return (exec_env(cmds));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (exec_echo(cmds, args, args_count));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (exec_cd(cmds, args));
	else if (ft_strcmp(args[0], "exit") == 0)
		exec_exit(cmds, args[1], *temp_env);
	else if (ft_strcmp(args[0], "export") == 0) 
		return (exec_export(cmds, args, temp_env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (exec_unset(cmds, args, temp_env)); // not work well
	
	return (0);
}

static	int	exec_pwd(t_cmd *cmds)
{
	char	*out;

	out = find_var(cmds->envp, "PWD=");
	if (out)
		printf("%s\n", out);
	else
		// return(error_msg(cmds, 1, "pwd"));
		return(error_msg(1, "pwd"));
	return (0);
}

int	exec_env(t_cmd *cmds)
{
	int	i;
	int	len;

	if (!cmds->envp)
		//return(error_msg(cmds, 1, "envp"));
		return(error_msg(1, "envp"));
	i = 0;
	len = ft_len_2d(cmds->envp);
	// while (cmds->envp[i] && i < len)
	while (i < len)
	{
		if (ft_strchr(cmds->envp[i], '=') && cmds->envp[i])
			printf("%s\n", cmds->envp[i]);
		i++;
	}
	return (0);
}
// need to handle case: unset MAIL->> it works normally in bash,
// our program works with unset $MAIL, for unset MAIL, it is not work

// static	int	exec_unset(t_cmd *cmds, char **args, char **env)
static	int	exec_unset(t_cmd *cmds, char **args, char ***temp_env)
{
	if (!temp_env || !args[1])
	{
		printf("Error: %s\n", args[1]);
		return (1);
	}
	else
	{
		printf("Reduce env\n");
		// return(reduce_env(cmds, args[1] env));
		return(reduce_env(cmds, args[1], temp_env));
	}
}

static	void	exec_exit(t_cmd *cmds, char *s, char **temp_env)
{
	int	status;

	printf("exit\n");
	if (s && ft_is_numeric(s))
		status = ft_atoi(s);
	else if (s)
	{
		printf("bash: exit: %s: numeric argument required\n", s);
		status = 2;
	}
	else
		status = 100;
	free_cmd(cmds);
	ft_free_triptr(&temp_env);
	exit(status);
	//return (0);
}