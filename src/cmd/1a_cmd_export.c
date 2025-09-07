/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_cmd_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/07 10:28:39 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//"export"
//a. When no option, it will sort the envp and printout.
//b. When have option: name "viet"
//    export name;-> this will assign variable to envp.

int	exec_export_only(t_cmd *cmds)
{
	int	i;
	char	**temp;
	printf("Export execute");
	if (!cmds->envp)
		return(error_msg(cmds, 1, "envp"));
	i  = 0;
	temp = ft_matrix_dup(cmds->envp, ft_len_2d(cmds->envp));
	if (!temp)
		return(error_malloc(cmds, 1));
	sort_2d_array(temp);
	while (temp[i])
	{
		if (ft_strchr(temp[i], '=') && temp[i][0] != '_')
			printf("%s\n", temp[i]);
		i++;
	}
	ft_free_triptr(&temp);
	return (0);
}
