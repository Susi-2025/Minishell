
#include "minishell.h"

void	setup_heredoc_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	setup_signals(); // restore the default interactive handlers
}

