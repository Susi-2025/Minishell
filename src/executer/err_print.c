
#include "minishell.h"

char	*error_redir(char *argv)
{
	ft_putstr_fd("bash: $", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": ambiguous redirect", 2);
	ft_putstr_fd("'\n", 2);
	return (NULL);
}

void	error_string(char *argv)
{
	char	error[1000];

	ft_strcpy(error, "bash: ");
	ft_strcat(error, argv);
	ft_strcat(error, ": ");
	ft_strcat(error, strerror(errno));
	ft_strcat(error, "\n");
	ft_putstr_fd(error, 2);
}

void	error_syntax(char *argv)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd("'\n", 2);
}