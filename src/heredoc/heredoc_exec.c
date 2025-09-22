
#include "minishell.h"

static	int	join_and_free(char **output, char *input);

int	heredoc_exec(t_cmd *cmds, char **env[], char **args, int args_count)
{
	char	*input;
	char	*output;
	int		exit_code;
	char	*path;
	int     pipefd[2];
    pid_t   pid;

	printf("Execute heredoc\n");
	output = ft_strdup("");
	// output = NULL;
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
		printf("Value of input: %s", input);
		printf("\n");
		if (join_and_free(&output, input) == 1)
			return (1);
	}
	if (cmds->here_doc_cont)
	// {
	// 	printf("Is this issue here\n");
		free(cmds->here_doc_cont);
	// }
	cmds->here_doc_cont = output;
	printf("Value of cmds->heredoc_cont: %s\n", cmds->here_doc_cont);
	if (!args)
		return (0);
	if (args[0] && check_built_in(args[0]) == 1)
	{
		if (ft_strcmp(args[0], "exit") == 0)
		{
			exit_code = exec_built_in(cmds, args, env, args_count);
			ft_free_triptr(env);
			free_cmd(cmds);
			exit (exit_code);
		}
		else
			exec_built_in(cmds, args, env, args_count);
	}
	else if (args[0])
	{
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
	// if (*output)
	// 	ft_strcpy(res, *output);
	i = 0;
	while (input && input[i])
		*ptr++ = input[i++];
	// if (input)
	// 	ft_strcat(res, input);
	*ptr++ = '\n';
	*ptr = '\0';
	if (*output)
		free(*output);
	if (input)
		free(input);
	*output = res;
	return (0);
}
