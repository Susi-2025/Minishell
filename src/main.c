/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:58:03 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/16 12:25:33 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_interactive = 1;


static int	read_heredoc_to_file(char *delimiter, char *filename)
{
	int		fd;
	char	*input;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (!input)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n", 2);
            break; 
        }
		if ((ft_strcmp(input, delimiter) == 0)
            && (ft_strlen(input) == ft_strlen(delimiter)))
        {
            free(input);
            break;
        }
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	return (0);
}

char *create_heredoc_file(void)
{
	static unsigned int file_counter;
	const char* path_start = ".here_doc";
	char	*temp_num;
	char	*path;

	path = NULL;
	while (path == NULL)
	{
		temp_num = ft_itoa(file_counter);
		file_counter++;
		if (!temp_num)
			return (NULL);
		path = ft_strjoin(path_start, temp_num);
		free(temp_num);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
		{
			free(path);
			path = NULL;
			continue ;
		}
	}
	return (path);
}

int handle_heredoc(t_vector *here_docs, char *delimiter)
{
	char	*filename;

	filename = create_heredoc_file();
	if (!filename)
		return (-1);
	printf("filename: %s\n", filename);
	if (read_heredoc_to_file(delimiter, filename) == -1)
	{
		free(filename);
		return (-1);
	}
	if (vector_push_back(here_docs, filename) == VECTOR_ERROR)
	{
		free(filename);
		return (-1);
	}
	return (0);
}
static int  check_initial_syntax(t_token *tokens, int token_count)
{
	if (token_count == 0)
		return (ERROR);

	if (token_count == 1 && tokens[0].type == TOKEN_EOF)
		return (SUCCESS);

	if (tokens[0].type == PIPE)
	{
		error_syntax(tokens[0].value);
		return (ERROR);
	}

	return (SUCCESS);
}

static int  syntax_error_at_token(t_token *token)
{
    if (token->type == TOKEN_EOF)
        error_syntax("newline");
    else
        error_syntax(token->value);
    return (ERROR);
}

static int  is_redirection(t_token_type type)
{
    return (type == HERE_DOC || type == REDIR_IN ||
            type == REDIR_OUT || type == REDIR_APPEND);
}

static int  check_token_in_loop(t_token *tokens, int i)
{
    if (is_redirection(tokens[i].type))
    {
        if (tokens[i + 1].type != WORD)
            return (syntax_error_at_token(&tokens[i + 1]));
    }

    if (tokens[i].type == PIPE)
    {
        if (tokens[i + 1].type == PIPE || tokens[i + 1].type == TOKEN_EOF)
            return (syntax_error_at_token(&tokens[i + 1]));
    }
    return (SUCCESS);
}

int syntax_checker(t_token *tokens, int token_count, t_vector *here_docs)
{
	int	i;

	i = 0;
	if (check_initial_syntax(tokens, token_count) == ERROR)
        return (ERROR);
	while (i < token_count && tokens[i].type != TOKEN_EOF)
	{
		if (check_token_in_loop(tokens, i) == ERROR)
            return (ERROR);
		if (tokens[i].type == HERE_DOC)
		{
			if (handle_heredoc(here_docs, tokens[i + 1].value) == -1)
				return (ERROR);
		}
		i++;
	}
	return SUCCESS;
}

t_cmd	*ft_prepare_command(char *line, char *env[], int error_code)
{
	int			token_count;
	t_token		*tokens;
	t_cmd		*cmds;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	cmds->err_code = error_code;

	cmds->heredoc_files = malloc(sizeof(t_vector));
    if (!cmds->heredoc_files)
    {
        free(cmds);
        return (NULL);
    }
	if (vector_setup(cmds->heredoc_files) == VECTOR_ERROR) // <-- NO '&'
    {
        free(cmds->heredoc_files);
        free(cmds);
        return (NULL);
    }

	tokens = tokenize(line, &token_count);
	if (!tokens)
	{
		vector_destroy(cmds->heredoc_files);
		free(cmds);
		return (NULL);
	}

	if (syntax_checker(tokens, token_count, cmds->heredoc_files) == ERROR) // <-- PASS BY POINTER
    {
        free_tokens(tokens, token_count);
        // We must destroy the vector (and unlink files) before freeing cmds
        vector_destroy_heredocs(cmds->heredoc_files); // <-- Custom free function
        free(cmds);
        return (NULL);
    }
	if (parse_tokens(cmds, tokens, token_count, env) == ERROR)
    {
        free_tokens(tokens, token_count);
        free_cmd(cmds); // free_cmd should also call vector_destroy_heredocs
        return (NULL);
    }
    free_tokens(tokens, token_count);

	// cmds = parse_tokens(tokens, token_count, env);
	// free_tokens(tokens, token_count);
	return (cmds);
}

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_interactive)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	(void)sig;
	if (g_interactive)
		return ;
}

void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

static	int	count_symbol(char *rl, char c)
{
	int	i;
	int	out;

	i = 0;
	out = 0;
	while (rl[i])
	{
		if (rl[i] == c)
			out++;
		i++;
	}
	return (out);
}

static	int	check_rl(char *rl)
{
	int	no_d_quote;
	int no_s_quote;
	
	no_d_quote = count_symbol(rl, '\"');
	no_s_quote = count_symbol(rl, '\'');
	// printf("Value of rl: %s\n", rl);
	// printf("Value of no_double_quote and single_quote: %i and %i \n", no_d_quote, no_s_quote);
	// if (no_d_quote % 2 != 0 || no_s_quote % 2 != 0)
	// {
	// 	printf("minishell: syntax error\n");
	// 	return (1);
	// }
	return (0);
}

int	main(int argc, char *argv[], char *init_env[])
{
	char	*rl;
	t_cmd	*cmds;
	char	**temp_env;
	int		code;
	// int		cmd_exit_code;
	// int		i;
	// int		j;
	(void)argc;
	(void)argv;
	setup_signals();
	temp_env = ft_matrix_dup(init_env, ft_len_2d(init_env));
	if (!temp_env)
		return (1);
	// cmds->err_code = 0;
	code = 0;
	while (1)
	{
		g_interactive = 1;
		rl = readline("Prompt: ");
		if (!rl)
		{
			printf("exit\n");
			break ;
		}
		if (*rl)
			add_history(rl);
		if (check_rl(rl))
		{}
		g_interactive = 0;
		
		cmds = ft_prepare_command(rl, temp_env, code);
		// 1. segmation fault when typing: 
		// echo "hello -> maybe just showed syntax error or something
		// 2. for case: 
		// echo $? -> the value of args[1] will be empty, could we store it as: $? ?
		// I think we need a err_code value for storing -> I put in structs.h
		if (cmds)
		{
			cmd_print(cmds);
			
			code = ft_pipex(cmds, &temp_env); //for updating temp_env inside the function
			// printf("Return code from previous command is: %d\n", code);
			if (cmds)
				free_cmd(cmds);
		}
		free(rl);
	}
	rl_clear_history();
	if (temp_env)
		ft_free_triptr(&temp_env);
	return (0);
}
// char *cmds = {cmd1, cmd2, cmd3, NULL};