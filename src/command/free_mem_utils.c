/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:34:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/22 14:34:17 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_2_mem(char *old_wd, char *next_wd, int exit_code)
{
	if (old_wd)
		free(old_wd);
	if (next_wd)
		free(next_wd);
	return (exit_code);
}

void	free_and_exit(t_cmd *cmds, char **temp_env, int status)
{
	free_cmd(cmds);
	ft_free_triptr(&temp_env);
	exit((unsigned char)status);
}
