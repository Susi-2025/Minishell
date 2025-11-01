/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:58:03 by cdohanic          #+#    #+#             */
/*   Updated: 2025/11/01 15:05:32 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_line(char ***temp_env, int *code);
static int	valid_len(char *rl);
static int	error_sigpipe(char *rl, char ***temp_env);
static int	err_rl(int *code);

volatile sig_atomic_t	g_signal;

int	main(int argc, char *argv[], char *init_env[])
{
	char	**temp_env;
	int		code;

	(void)argc;
	(void)argv;
	signal(SIGPIPE, sigpipe_handler);
	setup_signals();
	temp_env = ft_matrix_dup(init_env, ft_len_2d(init_env));
	if (!temp_env)
		return (1);
	code = 0;
	while (1)
	{
		if (run_line(&temp_env, &code) == -1)
			break ;
	}
	rl_clear_history();
	if (temp_env)
		ft_free_triptr(&temp_env);
	printf("exit\n");
	return (code);
}

static int	run_line(char ***temp_env, int *code)
{
	char	*rl;
	t_cmd	*cmds;

	clearerr(stdout);
	rl = readline("Prompt: ");
	if (g_signal == SIGPIPE)
		return (error_sigpipe(rl, temp_env));
	if (!rl)
		return (err_rl(code));
	add_history(rl);
	g_signal = 0;
	if (!valid_len(rl) || ft_strcmp(rl, "") == 0)
		return (0);
	cmds = ft_prepare_command(rl, *temp_env, code);
	free(rl);
	if (cmds)
	{
		*code = ft_pipex(cmds, temp_env);
		if (cmds)
			free_cmd(cmds);
	}
	if (!cmds && *code != 130)
		*code = 2;
	return (0);
}

static int	valid_len(char *rl)
{
	if (ft_strlen(rl) > 4096)
	{
		printf("ARG_MAX exceeded\n");
		free(rl);
		return (0);
	}
	return (1);
}

static int	error_sigpipe(char *rl, char ***temp_env)
{
	if (rl)
		free(rl);
	if (temp_env)
		ft_free_triptr(temp_env);
	return (-1);
}

static int	err_rl(int *code)
{
	if (g_signal == SIGINT)
	{
		printf("\n");
		*code = 130;
		g_signal = 0;
		return (0);
	}
	return (-1);
}
