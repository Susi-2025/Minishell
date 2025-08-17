
#include "minishell.h"

int	check_builtin(char *cmd)
{
	int	i;
	
	i = 0;
	
	if (ft_strnstr(cmd, "cd", 2)) // cmd == cde
		return (1);
	if (ft_strnstr(cmd, "env", 3))
		return (1);
	if (ft_strnstr(cmd, "pwd", 3))
		return (1);
	if (ft_strnstr(cmd, "echo", 4))
		return (1);
	if (ft_strnstr(cmd, "exit", 4))
		return (1);
	if (ft_strnstr(cmd, "unset", 5))
		return (1);
	if (ft_strnstr(cmd, "export", 6))
		return (1);
	return (0);
}