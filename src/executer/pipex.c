/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:41:08 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/21 19:11:22 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_and_fork_logic(t_object *pipex, int i, t_cmd *cmds, char *env[])
{
	if (i < pipex->num_commands - 1)
	{
		if (pipe(pipex->pipefd) == -1)
		{
			perror("pipe error");
			exit(1);
		}
	}
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	else if (pipex->pid == 0)
	{
		// printf("Running child process: %d\n", i);
		child_process(pipex, i, cmds, env);
	}
	else
		parent_process(pipex, i);
}

int	wait_for_children(t_object *pipex)
{ 
	// // printf("DEBUG: About to enter while(wait...)\n");
	// while (wait(&pipex->status) > 0)
	// {
	// 	// printf("DEBUG: wait() collected a child\n");
	// }
	// // printf("DEBUG: Finished waiting\n");
	// int exit_code = WEXITSTATUS(pipex->last_status);
	// // printf("DEBUG: Returning exit code: %d\n", exit_code);
	// return (exit_code);
	int	status;
	int	exit_code;
	pid_t	pid;
	// printf("DEBUG: Before waiting, last_child_pid = %d\n", pipex->last_child_pid);
	exit_code = 0;
	while ((pid = wait(&status)) > 0)
	{
		if (pid == pipex->last_child_pid)
		{
			exit_code = WEXITSTATUS(status);
			// printf("last pid: %d, exit status: %d\n", pipex->last_child_pid, exit_code);
		}
		exit_code = WEXITSTATUS(status);
	}
	return (exit_code);
}

// static	int		heredoc_read(t_cmd *cmds)
// {
// 	char	*input;
// 	char	*output;
	
// 	output = ft_strdup("");
// 	while (1)
// 	{
// 		input = readline("> ");
// 		if (!input)
// 			break ;
// 		if ((ft_strcmp(input, cmds->here_doc) == 0)
// 			&& (ft_strlen(input) == ft_strlen(cmds->here_doc)))
// 		{
// 			free(input);
// 			break ;
// 		}
// 		if (join_and_free(&output, input) == 1)
// 			return (1);
// 	}
// 	// printf("Out of loop\n");
// 	if (cmds->here_doc_cont)
// 		free(cmds->here_doc_cont);
// 	cmds->here_doc_cont = output;
// 	return (0);
// }

int	ft_pipex(t_cmd *cmds, char **env[])
{
	t_object	pipex;
	int			i;
	char		**args;
	int			args_count;
	// int			exit_code;

	if (!cmds)
		return (1);

	fire_up_pipeinator(&pipex, cmds);

	i = 0;
	while (i < pipex.num_commands)
	{
		args = cmds->simple_cmds[i]->args;
		args_count = cmds->simple_cmds[i]->args_count;
		if (cmds->cmds_count == 1 && check_built_in(args[0]) == 1)
		{
			cmds->err_code = exec_parent(cmds, args, env, args_count);
			return (cmds->err_code);
			// ft_printf_fd(2, "Return from parent exec: %d\n", cmds->err_code);
		}
		else
			pipe_and_fork_logic(&pipex, i, cmds, *env);
		i++;
	}
	last_close(&pipex);
	// if (pipex.last_child_pid != -1)
	// 	waitpid(pipex.last_child_pid, &pipex.last_status, 0);
	// while (wait(&pipex.status) > 0)
	//
	// return (WEXITSTATUS(pipex.last_status));
	// exit(WEXITSTATUS(pipex.last_status));
	return (wait_for_children(&pipex));
}

