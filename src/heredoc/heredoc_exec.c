/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:34:25 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/17 13:04:22 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// static	int	heredoc_read(t_cmd *cmds);
// static	void	child_pipe_heredoc(t_pipe_simple *pipex, t_cmd *cmds,
// 				char **args, char **env[]);
// static	void	parent_pipe_heredoc(t_pipe_simple *pipex, t_cmd *cmds);

// int	heredoc(t_cmd *cmds, char **env[], char **args, int args_count)
// {
// 	t_pipe_simple	pipe_heredoc;

// 	printf("Execute heredoc\n");
// 	if (heredoc_read(cmds) == 1)
// 		return (1);
// 	if (!args)
// 		return (0);
// 	if (args[0] && check_built_in(args[0]) == 1)
// 		exec_parent(cmds, args, env, args_count);
// 	else if (args[0] && check_built_in(args[0]) == 0)
// 	{
// 		printf("Execute external for here_doc\n");
// 		// execute with no input or output
// 		init_pipe_heredoc(&pipe_heredoc);
// 		if (open_pipe_heredoc(&pipe_heredoc) == 1)
// 			return (1);
// 		if (pipe_heredoc.pid == 0)
// 			child_pipe_heredoc(&pipe_heredoc, cmds, args, env);
// 		else
// 			parent_pipe_heredoc(&pipe_heredoc, cmds);
// 	}
// 	if (cmds->here_doc)
// 		cmds->here_doc = NULL;
// 	// if (cmds->here_doc_cont)
// 	// 	free(cmds->here_doc_cont);
// 	return (0);
// }

// static	void	child_pipe_heredoc(t_pipe_simple *pipex,
// 		t_cmd *cmds, char **args, char **env[])
// {
// 	char	*path;

// 	connect_pipe_heredoc(pipex);
// 	path = correct_path(args[0], *env);
// 	if (path != NULL)
// 	{
// 		free(args[0]);
// 		args[0] = path;
// 	}
// 	execve(args[0], args, *env);
// 	if (errno == ENOENT)
// 	{
// 		if (!path_exists(*env))
// 			error_string(args[0]);
// 		else
// 			failed_exec(args[0]);
// 	}
// 	else
// 		error_string(args[0]);
// 	free_cmd(cmds);
// 	ft_free_triptr(env);
// 	exit(127);
// }

// static	void	parent_pipe_heredoc(t_pipe_simple *pipex, t_cmd *cmds)
// {
// 	close(pipex->pipefd[0]);// close read end
// 	write(pipex->pipefd[1], cmds->here_doc_cont,
// 		ft_strlen(cmds->here_doc_cont));
// 	close(pipex->pipefd[1]);// EOF for child
// 	waitpid(pipex->pid, NULL, 0);
// }

// static	int	heredoc_read(t_cmd *cmds)
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
// 			// printf("Detect EOF\n");
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
// 	// printf("Value of here_doc_cont %s\n", cmds->here_doc_cont);
// 	return (0);
// }
