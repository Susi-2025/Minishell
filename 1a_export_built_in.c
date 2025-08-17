/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_export_built_in.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/17 18:19:49 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//"export"
//a. When no option, it will sort the envp and printout.
//b. When have option: name "viet"
//    export name;-> this will assign variable to envp.

int	exec_export_only(t_shell *shell)
{
	int	i;
	char	**temp;
	
	if (!shell->envp)
		return(error_msg(shell, 1, "envp"));
	i  = 0;
	temp = ft_matrix_dup(shell->envp, ft_len_2d(shell->envp));
	if (!temp)
		return(error_malloc(shell, 1));
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
