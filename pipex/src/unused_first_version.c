/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused_first_version.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:41:23 by cdohanic          #+#    #+#             */
/*   Updated: 2025/07/03 11:41:33 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
	/*
	if (argc < 5)
	{
		printf("you need more arguments\n");
		exit(1);
	}
	fd_init(&infile_fd, &outfile_fd, argv);
	pipe(pipefd);
	pid = fork();
    if (pid == 0)
    {
		printf("First child process (PID: %d)\n", getpid());
		if (infile_fd == -1)
			exit(0);
		dup2(infile_fd, STDIN_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
        close(pipefd[1]);

		cmd1 = parse_cmd(argv[2], env);
		if (!cmd1)
			cmd1 = cmd_error(argv[2]);
        execve(cmd1[0], cmd1, env);
		if (errno == ENOENT)
		{
			if (!path_exists(env))
				error_string(cmd1[0]);
			else
				failed_exec(cmd1[0]);
		}
		else
			error_string(cmd1[0]);
		exit(127);
    }

    pid = fork();
	if (pid == 0)
    {
 		printf("Second child process (PID: %d)\n", getpid());
		if (outfile_fd == -1)
			exit (1);
		dup2(outfile_fd, STDOUT_FILENO);
        dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);

		cmd2 = parse_cmd(argv[3], env);
		if (!cmd2)
			cmd2 = cmd_error(argv[3]);
        execve(cmd2[0], cmd2, env);
		if (errno == ENOENT)
		{
			if (!path_exists(env))
				error_string(cmd2[0]);
			else
				failed_exec(cmd2[0]);
		}
		else
			error_string(cmd2[0]);
		exit(127);
    }
	*/
    // close unused pipe
