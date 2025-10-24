/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:58:03 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/24 18:51:45 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	run_line(char ***temp_env, int *code);

volatile sig_atomic_t	g_signal;

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

	if (!rl)
	{
		if (temp_env)
			ft_free_triptr(temp_env);
		printf("exit\n");
		exit(*code);
	}
	add_history(rl);
	g_signal = 0;
	cmds = ft_prepare_command(rl, *temp_env, code);
	if (cmds)
	{
		*code = ft_pipex(cmds, temp_env);
		if (cmds)
			free_cmd(cmds);
	}
	if (!cmds && *code != 130)
		*code = 2;
	free(rl);
}
