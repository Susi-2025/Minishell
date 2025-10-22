/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:58:03 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/21 19:55:48 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_interactive = 1;

// t_cmd	*ft_prepare_command(char *line, char *env[], int error_code)
// {
// 	int			token_count;
// 	t_token		*tokens;
// 	t_cmd		*cmds;

// 	cmds = malloc(sizeof(t_cmd));
// 	if (!cmds)
// 		return (NULL);
// 	cmds->err_code = error_code;
// 	cmds->envp = env;

// 	cmds->heredoc_files = malloc(sizeof(t_vector));
//     if (!cmds->heredoc_files)
//     {
//         free(cmds);
//         return (NULL);
//     }
// 	if (vector_setup(cmds->heredoc_files) == VECTOR_ERROR)
//     {
//         free(cmds->heredoc_files);
//         free(cmds);
//         return (NULL);
//     }

// 	tokens = tokenize(line, &token_count);
// 	if (!tokens)
// 	{
// 		vector_destroy(cmds->heredoc_files);
// 		free(cmds);
// 		return (NULL);
// 	}

// 	if (syntax_checker(tokens, token_count, cmds) == ERROR)
//     {
//         free_tokens(tokens, token_count);
//         vector_destroy_heredocs(cmds->heredoc_files);
//         free(cmds);
//         return (NULL);
//     }
// 	if (parse_tokens(cmds, tokens, token_count, env) == ERROR)
//     {
//         free_tokens(tokens, token_count);
//         free_cmd(cmds); // free_cmd should also call vector_destroy_heredocs
//         return (NULL);
//     }
//     free_tokens(tokens, token_count);

// 	// cmds = parse_tokens(tokens, token_count, env);
// 	// free_tokens(tokens, token_count);
// 	return (cmds);
// }

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
		g_interactive = 0;
		
		cmds = ft_prepare_command(rl, temp_env, code);
		if (cmds)
		{
			// ft_printf_fd(2, "Value of previous err code: %d\n", cmds->err_code);
			// cmd_print(cmds);
			// error_cmd_fd(0, "exec", "test print fd", "success");
			//cmds->err_code = code;
			code = ft_pipex(cmds, &temp_env); //updating cmd->err_code inside
			//printf("EXIT CODE %d\n", code);
			
			// ft_printf_fd(2, "Value of current err code: %d\n", code);
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