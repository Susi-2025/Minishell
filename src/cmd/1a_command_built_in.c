/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_command_built_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/08 12:05:46 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	exec_pwd(t_cmd *cmds);
static	int	exec_env(t_cmd *cmds);
static	int	exec_unset(t_cmd *cmds);
static	int	exec_exit(t_cmd *cmds, char *s, char **temp_env);

//1. Command will return 0 for success and non-zero for fail.
//2. "env": Add checking = to make sure only printout line which has =
//3. "export, echo, cd"->separatre to new file

int exec_built_in(t_cmd *cmds, char **temp_env)
{
	printf("Exec built-in\n");
	if (!cmds || !cmds->simple_cmds || !cmds->simple_cmds[0]->args[0])
		//return(error_msg(cmds, 1, "cmds"));
		return(error_msg(1, "cmds"));
	if (ft_strcmp(cmds->simple_cmds[0]->args[0], "pwd") == 0)
		return (exec_pwd(cmds));
	else if (ft_strcmp(cmds->simple_cmds[0]->args[0], "env") == 0)
		return (exec_env(cmds));
	else if (ft_strcmp(cmds->simple_cmds[0]->args[0], "export") == 0 
			&& (!cmds->simple_cmds[0]->args[1])) 
		return (exec_export_only(cmds));//work-but no same as bash, need to change
	else if (ft_strcmp(cmds->simple_cmds[0]->args[0], "echo") == 0)
		return (exec_echo(cmds));
	else if (ft_strcmp(cmds->simple_cmds[0]->args[0], "cd") == 0)
		return (exec_cd(cmds));
	else if (ft_strcmp(cmds->simple_cmds[0]->args[0], "unset") == 0)
		return (exec_unset(cmds));
	else if (ft_strcmp(cmds->simple_cmds[0]->args[0], "exit") == 0)
		return (exec_exit(cmds, cmds->simple_cmds[0]->args[1], temp_env));
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

static	int	exec_env(t_cmd *cmds)
{
	int	i;

	if (!cmds->envp)
		//return(error_msg(cmds, 1, "envp"));
		return(error_msg(1, "envp"));
	i = 0;
	while (cmds->envp[i])
	{
		if (ft_strchr(cmds->envp[i], '='))
			printf("%s\n", cmds->envp[i]);
		i++;
	}
	return (0);
}

static	int	exec_unset(t_cmd *cmds)
{
	if (!cmds->envp || !cmds->simple_cmds[0]->args[1])
	{
		printf("Error: %s\n", cmds->simple_cmds[0]->args[1]);
		return (1);
	}
	else
	{
		printf("Reduce env\n");
		return(reduce_env(cmds, cmds->simple_cmds[0]->args[1]));
	}
}

static	int	exec_exit(t_cmd *cmds, char *s, char **temp_env)
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
		status = 0;
	free_cmd(cmds);
	ft_free_triptr(&temp_env);
	exit(status);
	return (0);
}