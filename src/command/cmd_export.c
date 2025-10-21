/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/21 14:47:17 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_export(t_cmd *cmds, char **args, char ***temp_env)
{
	int		i;

	if (args[1] == NULL)
		return (exec_export_only(cmds));
	i = 1;
	while (args[i])
	{
		if (invalid_args(args[i]))
		{
			ft_printf_fd(2, "invalid happen\n");
			error_string_export(args[i]);
			i++;
		}
		if (export_with_args(cmds, args[i], temp_env) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	export_with_args(t_cmd *cmds, char *arg_str, char ***temp_env)
{
	char	*args_heads;
	char	*value;

	ft_printf_fd(2, "Start export with args\n");
	if (ft_strchr(arg_str, '='))
		args_heads = ft_strhead(arg_str, '=');
	else
		args_heads = arg_str;
	if (check_var_env(*temp_env, args_heads) == 0)
	{
		ft_printf_fd(2,"No found var, start to insert\n");
		if (insert_env(cmds, arg_str, temp_env) == 1)
			return (1);
	}
	else if (ft_strchr(arg_str, '=') == 1
		&& check_var_env(*temp_env, args_heads) == 1)
	{
		value = ft_strtail(arg_str, '=');
		ft_printf_fd(2, "found and start to update\n");
		if (update_env(cmds, args_heads, value) == 1)
			return (1);
		if (value)
			free(value);
	}
	if (ft_strchr(arg_str, '='))
		free(args_heads);
	return (0);
}

int	exec_export_only(t_cmd *cmds)
{
	int		i;
	char	**temp;

	if (!cmds->envp)
		return (error_msg(1, "envp"));
	i = 0;
	temp = ft_matrix_dup(cmds->envp, ft_len_2d(cmds->envp));
	if (!temp)
		return (1);
	sort_2d_array(temp);
	while (i < ft_len_2d(temp))
	{
		if (temp[i][0] == '_' && temp[i][1] == '=')
			i++;
		if (temp[i] && i < ft_len_2d(temp))
			printf_for_export(temp[i]);
		i++;
	}
	ft_free_triptr(&temp);
	return (0);
}
