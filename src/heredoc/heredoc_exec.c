
#include "minishell.h"

void	heredoc_exec(t_cmd *cmds, char **env[], char **args, int args_count)
{
	char	*here_rl;
	printf("Execute heredoc\n");
	(void) cmds;
	(void) env;
	(void) args;
	(void) args_count;
	while (1)
	{
		here_rl = readline("> ");
		if (ft_strcmp(here_rl, cmds->here_doc) == 0)
			break;
		printf("Value of input: %s", here_rl);
		printf("\n");
	}
}