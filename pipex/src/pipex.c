/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:41:08 by cdohanic          #+#    #+#             */
/*   Updated: 2025/07/03 14:29:29 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	pipe_and_fork_logic(t_object *pipex, int i, char *argv[], char *env[])
{
	if (i < pipex->num_commands - 1)
	{
		if (pipe(pipex->pipefd) == -1)
		{
			perror("pipenberg");
			exit(1);
		}
	}
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		perror("forkgzz");
		exit(1);
	}
	else if (pipex->pid == 0)
		child_process(pipex, i, argv, env);
	else
		parent_process(pipex, i);
}

int	main(int argc, char *argv[], char *env[])
{
	t_object	pipex;
	int			i;

	if (argc < 5)
	{
		ft_putstr_fd("Hello partner! Consider giving more parameters!\n", 2);
		exit(1);
	}
	fd_init(&pipex.infile_fd, &pipex.outfile_fd, argv[1], argv[argc - 1]);
	fire_up_pipeinator(&pipex, argc);
	i = 0;
	while (i < pipex.num_commands)
	{
		pipe_and_fork_logic(&pipex, i, argv, env);
		i++;
	}
	last_close(&pipex);
	if (pipex.last_child_pid != -1)
		waitpid(pipex.last_child_pid, &pipex.last_status, 0);
	while (wait(&pipex.status) > 0)
		;
	exit(WEXITSTATUS(pipex.last_status));
}
