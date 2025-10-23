/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:58:03 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/22 20:04:32 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	run_line(char ***temp_env, int *code);

volatile sig_atomic_t	g_interactive = 1;

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
	return (0);
}

static	void	run_line(char ***temp_env, int *code)
{
	char	*rl;
	t_cmd	*cmds;

	g_interactive = 1;
	rl = readline("Prompt: ");
	if (!rl)
	{
		if (temp_env)
			ft_free_triptr(temp_env);
		printf("exit\n");
		exit(*code);
	}
	if (*rl)
		add_history(rl);
	g_interactive = 0;
	cmds = ft_prepare_command(rl, *temp_env, *code);
	if (cmds)
	{
		*code = ft_pipex(cmds, temp_env);
		if (cmds)
			free_cmd(cmds);
	}
	free(rl);
}
