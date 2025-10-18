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

# define ERROR -1
# define SUCCESS 0
volatile sig_atomic_t	g_interactive = 1;

int syntax_checker(t_token *tokens, int token_count)
{
	int	i;

	if (token_count == 0)
		return (ERROR);
	if (tokens[0].type == PIPE)
	{
		error_syntax(tokens[0].value);
		return (ERROR);
	}
	i = 0;
	while (i < token_count && tokens[i].type != TOKEN_EOF)
	{

		if (tokens[i].type == PIPE)
		{
			if (tokens[i + 1].type == REDIR_OUT || tokens[i + 1].type == REDIR_IN)
			{
				i++;
				continue ;
			}
			if (tokens[i + 1].type == TOKEN_EOF || tokens[i + 1].type != WORD)
			{
				if (tokens[i + 1].type == TOKEN_EOF)
					error_syntax("newline");
				else
					error_syntax(tokens[i + 1].value);
				return (ERROR);
			}
		}
		i++;
	}
	return SUCCESS;
}

t_cmd	*ft_prepare_command(char *line, char *env[])
{
	int		token_count;
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenize(line, &token_count);
	if (!tokens)
		return (NULL);
	if (syntax_checker(tokens, token_count) == ERROR)
	{
		free_tokens(tokens, token_count);
		return (NULL);
	}
	printf("value of token count: %i\n", token_count);
	cmds = parse_tokens(tokens, token_count, env);
	free_tokens(tokens, token_count);
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
	if (no_d_quote % 2 != 0 || no_s_quote % 2 != 0)
	{
		printf("minishell: syntax error\n");
		return (1);
	}
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
			break ;
		g_interactive = 0;
		cmds = ft_prepare_command(rl, temp_env);
		// 1. segmation fault when typing: 
		// echo "hello -> maybe just showed syntax error or something
		// 2. for case: 
		// echo $? -> the value of args[1] will be empty, could we store it as: $? ?
		// I think we need a err_code value for storing -> I put in structs.h
		if (cmds)
		{
			cmd_print(cmds);
			cmds->err_code = code;
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