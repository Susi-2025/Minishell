/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_support.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 20:07:55 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/24 20:15:47 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

int	heredoc_signal_hook(void)
{
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}

void	setup_heredoc_signals(void)
{
	rl_event_hook = heredoc_signal_hook;
	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	g_signal = 0;
	rl_done = 0;
	rl_event_hook = NULL;
	setup_signals();
}

int	free_return(char **str, int code)
{
	if (*str)
		free(*str);
	return (code);
}
