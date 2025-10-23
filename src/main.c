/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:58:03 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/23 20:44:45 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	run_line(char ***temp_env, int *code);

volatile sig_atomic_t	g_interactive = 1;

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_interactive == 1)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_interactive == 2)
	{
		close(STDIN_FILENO);
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
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		perror("sigaction");
	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction");
}

int	main(int argc, char *argv[], char *init_env[])
{
	char	**temp_env;
	int		code;

	(void)argc;
	(void)argv;
	setup_signals();
	temp_env = ft_matrix_dup(init_env, ft_len_2d(init_env));
	if (!temp_env)
		return (1);
	code = 0;
	while (1)
		run_line(&temp_env, &code);
	rl_clear_history();
	if (temp_env)
		ft_free_triptr(&temp_env);
	return (code);
}

static	void	run_line(char ***temp_env, int *code)
{
	char	*rl;
	t_cmd	*cmds;

	g_interactive = 1;
	//for running 2800 test case
	// char *line;
	// line = get_next_line(fileno(stdin));
	// if (!line)
	// {
	// 	// printf("exit\n");
	// 	exit(*code);
	// }
	// rl = ft_strtrim_v(line, "\n");
	// free(line);
	// official running
	rl = readline("Prompt: ");
	if (!rl)
	{
		if (temp_env)
			ft_free_triptr(temp_env);
		printf("exit\n");
		exit(*code);
	}
	add_history(rl);
	g_interactive = 0;
	cmds = ft_prepare_command(rl, *temp_env, code);
	if (cmds)
	{
		*code = ft_pipex(cmds, temp_env);
		if (cmds)
			free_cmd(cmds);
	}
	if (!cmds && *code != 130)
		*code = 2;
	printf("CODE: %d\n", *code);
	free(rl);
}
