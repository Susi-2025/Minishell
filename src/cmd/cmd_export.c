/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_cmd_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/08 12:05:35 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//"export"
//a. When no option, it will sort the envp and printout.
//b. When have option: name "viet"
//    export name;-> this will assign variable to envp.-> do we need to handle it?
static	void	printf_for_export(char *str);

int	exec_export_only(t_cmd *cmds)
{
	int	i;
	char	**temp;
	printf("Export execute\n");
	if (!cmds->envp)
		//return(error_msg(cmds, 1, "envp"));
		return(error_msg(1, "envp"));
	i  = 0;
	temp = ft_matrix_dup(cmds->envp, ft_len_2d(cmds->envp));
	if (!temp)
		// return(error_malloc(cmds, 1));
		return (1);
	sort_2d_array(temp);
	while (temp[i])
	{
		if (ft_strchr(temp[i], '=') && temp[i][0] != '_')
			printf_for_export(temp[i]);
		i++;
	}
	ft_free_triptr(&temp);
	return (0);
}

static	void	printf_for_export(char *str)
{
	int	i;
	
	printf("declare -x ");
	i = 0;
	while(str[i] &&str[i] != '=')
	{
		printf("%c", str[i]);
		i++;
	}
	if (str[i] == '=')
	{
		//printf("=");
		printf("=\"%s\"", &str[i + 1]);
	}
	printf("\n");
}