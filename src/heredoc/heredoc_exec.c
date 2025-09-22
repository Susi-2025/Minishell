/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:34:25 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/22 13:34:52 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	join_and_free(char **output, char *input);

int	heredoc_exec(t_cmd *cmds, char **env[], char **args, int args_count)
{
	char	*input;
	char	*output;
	// int		exit_code;
	char	*path;
	int     pipefd[2];
    pid_t   pid;

	printf("Execute heredoc\n");
	output = ft_strdup("");
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			printf("Error\n");
			break;
		}
		if ((ft_strcmp(input, cmds->here_doc) == 0)
			&& (ft_strlen(input) == ft_strlen(cmds->here_doc)))
		{
			free(input);
			break;
		}
		if (join_and_free(&output, input) == 1)
			return (1);
	}
	if (cmds->here_doc_cont)
		free(cmds->here_doc_cont);
	cmds->here_doc_cont = output;
	if (!args)
		return (0);
	if (args[0] && check_built_in(args[0]) == 1)
		exec_parent(cmds, args, env, args_count);
	else if (args[0] && check_built_in(args[0]) == 0)
	{
		printf("Execute external for here_doc\n");
		if (pipe(pipefd) == -1)
    	{
        	perror("pipe");
        	return (1);
    	}
    	pid = fork();
    	if (pid == -1)
	    {
        	perror("fork");
        	return (1);
	    }
    	if (pid == 0) // child
    	{
    	    close(pipefd[1]); // close write end
        	dup2(pipefd[0], STDIN_FILENO); // redirect stdin
        	close(pipefd[0]);
			path = correct_path(args[0], *env);
			if (path != NULL)
			{
				free(args[0]);
				args[0] = path;
			}
			execve(args[0], args, *env);
			if (errno == ENOENT)
			{
				if (!path_exists(*env))
					error_string(args[0]);
				else
					failed_exec(args[0]);
			}
			else
				error_string(args[0]);
			free_cmd(cmds);
			ft_free_triptr(env);
			exit(127);
		}
		else // parent
    	{
        	close(pipefd[0]); // close read end
        	write(pipefd[1], cmds->here_doc_cont, ft_strlen(cmds->here_doc_cont));
        	close(pipefd[1]); // EOF for child
        	waitpid(pid, NULL, 0);
		}
    }
	if (cmds->here_doc)
		cmds->here_doc = NULL;
	// if (cmds->here_doc_cont)
	// 	free(cmds->here_doc_cont);
	return (0);
}

static	int	join_and_free(char **output, char *input)
{
	char	*res;
	char	*ptr;
	int		i;

	res = (char *)malloc(ft_strlen(*output) + ft_strlen(input) + 2);
	if (!res)
		return (1);
	ptr = res;
	i = 0;
	while (*output && (*output)[i])
		*ptr++ = (*output)[i++];
	i = 0;
	while (input && input[i])
		*ptr++ = input[i++];
	*ptr++ = '\n';
	*ptr = '\0';
	if (*output)
		free(*output);
	if (input)
		free(input);
	*output = res;
	return (0);
}
