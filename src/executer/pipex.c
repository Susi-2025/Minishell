/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:41:08 by cdohanic          #+#    #+#             */
/*   Updated: 2025/09/09 17:16:30 by vinguyen         ###   ########.fr       */
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
	//	printf("Running child process: %d\n", i);
		child_process(pipex, i, cmds, env);
	}
	else
		parent_process(pipex, i);
}


	// if (pipex.last_child_pid != -1)
	// 	waitpid(pipex.last_child_pid, &pipex.last_status, 0);
	// while (pipex->num_commands > 1 && (&pipex.status) > 0)
	// 	;
	// exit(WEXITSTATUS(pipex.last_status));
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


    int status;
    int exit_code = 0;
    pid_t pid;
	// printf("DEBUG: Before waiting, last_child_pid = %d\n", pipex->last_child_pid);
    while ((pid = wait(&status)) > 0)
    {
        if (pid == pipex->last_child_pid)
		{
			exit_code = WEXITSTATUS(status);
			// printf("last pid: %d, exit status: %d\n", pipex->last_child_pid, exit_code);
		}
            exit_code = WEXITSTATUS(status);
    }
    return exit_code;
}


// TASKS
// Analyze the code: get a good understanding of it
// Remove redundant things: remove some stuff from s_object struct
// understand error number output.. since you are in the same shell all the time.. you don t want to use exit? maybe?
// add syntax checker in parsing
// add builtins
// add here_doc and append
int	ft_pipex(t_cmd *cmds, char *env[])
{
	t_object	pipex;
	int			i;
	char		**args;
	int			args_count;
	int			exit_code;

	if (!cmds)
		return (1);
	fd_init(&pipex.infile_fd, &pipex.outfile_fd, cmds->in_file, cmds->out_file);
	fire_up_pipeinator(&pipex, cmds);
	i = 0;
	while (i < pipex.num_commands)
	{
	//	printf("execute the cmd: %d: %s\n", i, cmds->simple_cmds[i]->args[0]);
	// if 01 command: only run in parent process
		args = cmds->simple_cmds[i]->args;
		args_count = cmds->simple_cmds[i]->args_count;
		if (check_built_in(args[0]) == 1)
		{
			printf("Execute builtin not in fork\n");
			if (ft_strcmp(args[0], "exit") == 0)
			{
				exit_code = exec_built_in(cmds, args, env, args_count);
				ft_free_triptr(&env);
				free_cmd(cmds);
				exit (exit_code);
			}
			else
				exec_built_in(cmds, args, env, args_count);
			//exit (0);
		}
		// else if (cmds->cmds_count == 1 && check_built_in(args[0]) != 1)
		// {
		// 	//printf("Need to run in the fork");
		// 	pipe_and_fork_logic(&pipex, i, cmds, env);
		// }
		// else if (cmds->cmds_count > 1)
		else
			pipe_and_fork_logic(&pipex, i, cmds, env);
			// still show memory leakage if we input the wrong commands
		i++;
	}
	last_close(&pipex);
	// if (pipex.last_child_pid != -1)
	// 	waitpid(pipex.last_child_pid, &pipex.last_status, 0);
	// while (wait(&pipex.status) > 0)
	// 	;
	// return (WEXITSTATUS(pipex.last_status));
	// exit(WEXITSTATUS(pipex.last_status));

    return (wait_for_children(&pipex));
}
