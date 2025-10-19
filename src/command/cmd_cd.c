/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/19 17:53:06 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	change_dir(t_cmd *cmds, char *next_wd);
static	int	free_2_mem(char *old_wd, char *next_wd, int exit_code);
static	char	*get_parent_dir(char **envp);

int	exec_cd(t_cmd *cmds, char **args)
{
	char	*next_wd;

	next_wd = NULL;
	if (!cmds)
		return (error_msg(1, "cmds"));
	if (args[2])
		return (error_string_cd_1("too many arguments", 1));
	if ((args[1] == NULL) || ft_strcmp(args[1],"~") == 0)
	{
		next_wd = find_var(cmds->envp, "HOME");
		if (!next_wd)
			return (error_string_cd("HOME", 1));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		next_wd = find_var(cmds->envp, "OLDPWD");
		if (!next_wd)
			return (error_string_cd("OLDPWD", 1));
	}
	else 
		next_wd = args[1];
	if (!next_wd)
		return (1);
	printf("Before changing dir: next_wd is %s\n", next_wd);
	if (change_dir(cmds, next_wd) == 1)
		return (1);
	return (0);
}

static	char	*get_parent_dir(char **envp)
{
	char	*pwd;
	char	*dup;
	char	*par_pwd;

	pwd = find_var(envp, "PWD");
	if (!pwd)
		return (NULL);
	dup = ft_strdup(pwd);
	if (!dup)
		return (NULL);
	par_pwd = ft_strjoin(dup, "/..");
	free(dup);
	if(!par_pwd)
		return (NULL);
	return (par_pwd);
}

static	int	change_dir(t_cmd *cmds, char *next_wd)
{
	char	*old_wd;
	char	*temp_wd;

	
	old_wd = ft_strdup(find_var(cmds->envp, "PWD"));
	if (!old_wd)
		return (1);
	if (chdir(next_wd) != 0)
	{
		//perror("cd");// need to modify again to show the correct message
		error_string_cd_2(next_wd, 1);
		return (free_2_mem(old_wd, NULL, 1));
	}
	temp_wd = getcwd(NULL, 0);
	if (!temp_wd)
	{
		printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
    	temp_wd = get_parent_dir(cmds->envp);
		if (!temp_wd)
			return (free_2_mem(old_wd, NULL, 1));
	}
	next_wd = temp_wd;
	if (update_env(cmds, "OLDPWD", old_wd) != 0 || update_env(cmds, "PWD", next_wd) != 0)
		return (free_2_mem(old_wd, next_wd, 1));
	return (free_2_mem(old_wd, next_wd, 0));
}

static	int	free_2_mem(char *old_wd, char *next_wd, int exit_code)
{
	if (old_wd)
		free(old_wd);
	if (next_wd)
		free(next_wd);
	return (exit_code);
}

int	error_string_cd_1(char *argv, int code)
{
	char	error[1000];

	ft_strcpy(error, "bash: ");
	ft_strcat(error, "cd: ");
	ft_strcat(error, argv);
	ft_strcat(error, "\n");
	ft_putstr_fd(error, 2);
	return  (code);
}

int	error_string_cd_2(char *argv, int code)
{
	char	error[1000];

	ft_strcpy(error, "bash: ");
	ft_strcat(error, "cd: ");
	ft_strcat(error, argv);
	ft_strcat(error, " : No such file or directory\n");
	ft_putstr_fd(error, 2);
	return  (code);
}