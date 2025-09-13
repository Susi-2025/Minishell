/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_single.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:54 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/09 11:35:48 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	int	check_built_in(char *cmd);
// static	int	command_run(t_cmd *cmds, char **args, char **temp_env);

// int	execution_single(t_cmd *cmds, char **temp_env)
// {
// 	char	**args;
// 	int		args_count;
	
// 	//printf("Execution Single Start\n");
// 	args = cmds->simple_cmds[0]->args;
// 	args_count = cmds->simple_cmds[0]->args_count;
// 	if (check_built_in(args[0]) == 1)
// 		return (exec_built_in(cmds, args, temp_env, args_count));// work well, not for option, only simple case
// 	else
// 		return (exec_external(cmds, args, temp_env));
// 	return (0);
// }

int	check_built_in(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0) 
		return (1);
	if (ft_strcmp(cmd, "echo") == 0) 
		return (1);
	if (ft_strcmp(cmd, "exit") == 0) 
		return (1);
	if (ft_strcmp(cmd, "unset") == 0) 
		return (1);
	if (ft_strcmp(cmd, "export") == 0) 
		return (1);
	return (0);
}

// int exec_external(t_cmd *cmds, char **args, char **temp_env)
// {
//     char *path;
// 	pid_t	pid;

//     path = correct_path(args[0], cmds->envp);
//     if (path != NULL)
//     {
//         free(args[0]);
//         args[0] = path;
//     }
// 	pid = fork();
//     if (pid == 0)
// 		return (command_run(cmds, args, temp_env));
//     else if (pid > 0)
//     {
//         int status;
//         waitpid(pid, &status, 0);
//         return WEXITSTATUS(status);
//     }
//     else
//     {
//         perror("fork");
//         return (1);
//     }
// }

// static	int	command_run(t_cmd *cmds, char **args, char **temp_env)
// {
// 	execve(args[0], args, cmds->envp);
//     if (errno == ENOENT)
//     {
//         if (!path_exists(cmds->envp))
//             error_string(args[0]);
//         else
//             failed_exec(args[0]);
//     }
//     else
// 		error_string(args[0]);
// 	free_cmd(cmds);
// 	ft_free_triptr(&temp_env);
//     exit(127);
// }