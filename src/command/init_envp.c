/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:31:23 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/23 15:13:35 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_envp(t_cmd *cmds, char **envp)
{
	int	len;

	if (!envp)
		return (1);
	len = ft_len_2d(envp);
	cmds->envp = ft_matrix_dup(envp, len);
	if (!cmds->envp)
		return (1);
	return (0);
}
