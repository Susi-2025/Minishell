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

static	void	printf_for_export(char *str);

int	exec_export(t_cmd *cmds, char **args, char ***temp_env)
{
	if (args[1] == NULL)
		return (exec_export_only(cmds));
	else if (ft_strchr(args[1], '='))
	{
		printf("Exec export with args\n");
		return (insert_env(cmds, args[1], temp_env));
		// return (insert_env(args[1], &temp_env));
	}
	else
	{
		printf("Error in args\n");
		return (1); //need the message about error here
	}
}

int	exec_export_only(t_cmd *cmds)
{
	int	i;
	char	**temp;

	// printf("Export execute\n");
	if (!cmds->envp)
		//return(error_msg(cmds, 1, "envp"));
		return (error_msg(1, "envp"));
	i = 0;
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
	while (str[i] && str[i] != '=')
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
