/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:31:04 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/23 18:31:11 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(t_cmd *cmds, char **arg_str, char ***temp_env, int args_count)
{
	int	i;

	i = 1;
	while (i < args_count)
	{
		if (check_var_env(*temp_env, arg_str[i]) == 1)
		{
			if (reduce_env(cmds, arg_str[i], temp_env) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
