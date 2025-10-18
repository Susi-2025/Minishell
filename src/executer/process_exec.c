/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:31:50 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/13 17:30:41 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cmd(t_object *pipex, int i, t_cmd *cmds, char *env[])
{
	char	**args;
	char	*path;
	int		args_count;
	int		exit_code;
	//Eliminate this struct
	(void)pipex;
	if (i >= cmds->cmds_count || !cmds->simple_cmds[i])
	{
		error_string("Invalid command index.");
		exit(127);
	}
	args = cmds->simple_cmds[i]->args;
	args_count = cmds->simple_cmds[i]->args_count;
	if (check_built_in(args[0]) == 1)
	{
		exit_code = exec_built_in(cmds, args, &env, args_count);
		// need to free memory cmd, env before
		free_cmd(cmds);
		ft_free_triptr(&env);
		exit(exit_code);
	}
	else 
	// if (check_built_in(args[0]) != 1)
	{
		// printf("Execute external in pipex\n");
		path = correct_path(args[0], env);
		if (path != NULL)
		{
			free(args[0]);
			args[0] = path;
		}
		// printf("args[0]: %s\n", args[0]);
		// if (!args[0])
		// {
		// 	printf("we are here");
		// 	error_string(args[0]);
		// 	exit(127);
		// }
		// STDIN -> {grep, -a, by, NULL}-> STDOUT
		execve(args[0], args, env);
		if (errno == ENOENT)
		{
			if (!path_exists(env))
				error_string(args[0]);
			else
				failed_exec(args[0]);
		}
		else
			error_string(args[0]);
		free_cmd(cmds);
		ft_free_triptr(&env);
		exit(127);
	}
}

// OLD EXECUTION

// void	reading_pipe(t_object *pipex, t_cmd *cmds, char *env[], int i)
// {
// 	if (i != 0)
// 	{
// 		// we wrote to pipefd[1] now we want to read from that same pipe from pipefd
// 		// if (infile)
// 		//	dup2()
// 		dup2(pipex->prev_pipe_in, STDIN_FILENO);
// 		close(pipex->prev_pipe_in);
// 	}
// 	else if (pipex->status[0] == FILE_ERROR)
// 	{
// 		free_cmd(cmds);
// 		ft_free_triptr(&env);
// 		exit(1);
// 	}
// 	else if (pipex->status[0] == FILE_VALID)
// 	{
// 		dup2(pipex->infile_fd, STDIN_FILENO);
// 		close(pipex->infile_fd);
// 	}
// }

// void	writing_pipe(t_object *pipex, t_cmd *cmds, char *env[], int i)
// {
// 	if (i == pipex->num_commands - 1)
// 	{
// 		if (pipex->status[1] == FILE_VALID)
// 		{
// 			dup2(pipex->outfile_fd, STDOUT_FILENO);
// 			close(pipex->outfile_fd);
// 		}
// 		else if (pipex->status[1] == FILE_ERROR)
// 		{
// 			free_cmd(cmds);
// 			ft_free_triptr(&env);
// 			exit(1);
// 		}
// 	}
// 	else
// 	{
// 		dup2(pipex->pipefd[1], STDOUT_FILENO);
// 		close(pipex->pipefd[1]);
// 		close(pipex->pipefd[0]);
// 	}
// }

// Helper function to open the LAST file in a list of redirections.
// Returns the file descriptor, or -1 on error.
int open_last_file(t_vector *files, int flags, t_cmd *cmds, char *env[])
{
    int i = 0;
    int last_fd = -1;

    if (!files)
        return (-1); // No files to open.

    while (i < files->args_count)
    {
        // Close the previously opened file descriptor in this sequence.
        if (last_fd != -1)
            close(last_fd);

        // Open the current file.
        if (flags & O_CREAT)
            last_fd = open(files->args[i], flags, 0644);
        else
            last_fd = open(files->args[i], flags);

        // If any file in the list fails to open, the whole command fails.
        if (last_fd == -1)
        {
			error_string(files->args[i]);
			free_cmd(cmds);
			ft_free_triptr(&env);
			exit(1);
        }
        i++;
    }
    return (last_fd); // Return the FD of the last successfully opened file.
}

// This function runs INSIDE the child to set up its STDIN and STDOUT.
void handle_io_redirection(t_simple_cmd *cmd, t_object *pipex, t_cmd *cmds, char *env[])
{
   	pipex->outfile_fd = open_last_file(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, cmds, env);
    
    if (pipex->outfile_fd != -1)
    {
        dup2(pipex->outfile_fd, STDOUT_FILENO);
        close(pipex->outfile_fd);
    }

    pipex->infile_fd = open_last_file(cmd->in_file, O_RDONLY, cmds, env);
    if (pipex->infile_fd != -1)
    {
        dup2(pipex->infile_fd, STDIN_FILENO);
        close(pipex->infile_fd);
    }
}

void	child_process(t_object *pipex, int i, t_cmd *cmds, char *env[])
{
	// 1. REDIRECTIONS: The child opens its own files.
    // This function will exit() the child on failure.
	// 2. PIPE INPUT: Connect stdin to the previous command's output.
    // This is ignored if there are file redirections, as dup2 will overwrite it.
    if (i > 0)
    {
        dup2(pipex->prev_pipe_in, STDIN_FILENO);
        close(pipex->prev_pipe_in);
    }
	// 3. PIPE OUTPUT: Connect stdout to the next command's input.
    // This is also ignored if there are file redirections.
    if (i != pipex->num_commands - 1)
    {
        dup2(pipex->pipefd[1], STDOUT_FILENO);
    }

    // 4. CLEANUP: Close all pipe ends that this child doesn't need.
    // A child should NEVER have the pipe FDs open when it calls execve.
	if (i != pipex->num_commands - 1)
	{
    	close(pipex->pipefd[0]);
    	close(pipex->pipefd[1]);
	}
    handle_io_redirection(cmds->simple_cmds[i], pipex, cmds, env);
	if (cmds->simple_cmds[i]->args[0] != NULL)
		run_cmd(pipex, i, cmds, env);
	else
	{
		free_cmd(cmds);
		ft_free_triptr(&env);
		exit(0);
	}
}

void	parent_process(t_object *pipex, int i)
{
	if (i > 0)
		close(pipex->prev_pipe_in);
	// if this is first cmd 
	if (i < pipex->num_commands - 1)
	{
		pipex->prev_pipe_in = pipex->pipefd[0]; 
		close(pipex->pipefd[1]);
	}
	if (i == pipex->num_commands - 1)
		pipex->last_child_pid = pipex->pid;
}
