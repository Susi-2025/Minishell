/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1z_command_utility.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/17 12:52:28 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var(char **envp, char *str)
{
	int		i;

	if (!envp || !str)
		return (NULL) ;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0
			&& envp[i][ft_strlen(str)] == '=')
		{
			return (envp[i]);
			break;
		}
		i++;
	}
	return (NULL);
}