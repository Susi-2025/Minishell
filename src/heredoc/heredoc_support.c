
#include "minishell.h"


void handle_heredoc_sigint(int sig)
{
	(void) sig;
	g_signal = SIGINT;
}

int    heredoc_signal_hook(void)
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
	// struct sigaction	sa;

	// sa.sa_handler = handle_heredoc_sigint;
	// sigemptyset(&sa.sa_mask);
	// sa.sa_flags = 0;
	// if (sigaction(SIGINT, &sa, NULL) == -1)
	// 	perror("sigaction");
	// signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	g_signal = 0;
	rl_done = 0;
	rl_event_hook = NULL;
	setup_signals(); // restore the default interactive handlers
}
