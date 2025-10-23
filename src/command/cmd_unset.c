
#include "minishell.h"

int	exec_unset(t_cmd *cmds, char **arg_str, char ***temp_env, int args_count)
{
	char	*args_heads;

	i = 1;
	while (i < args_count - 1)
	{
		if (ft_strchr(arg_str, '='))
			args_heads = ft_strhead(arg_str, '=');
		else
			args_heads = arg_str;
		if (check_var_env(*temp_env, args_heads) == 1)
		{
			if (reduce_env(cmds, args[1], temp_env) == 1)
				return (1);
		}
		free(args_heads);
		i++;
	}
}