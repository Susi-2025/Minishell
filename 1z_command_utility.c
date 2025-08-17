/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1z_command_utility.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/08/17 15:28:50 by vinguyen         ###   ########.fr       */
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
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
		{
			return (envp[i]);
			break;
		}
		i++;
	}
	return (NULL);
}

void	sort_2d_array(char **strs)
{
	int	i;
	int	j;
	int	len;
	char	*temp;

	i = 0;
	len = ft_len_2d(strs);
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(strs[i], strs[j]) > 0)
			{
				temp = strs[i];
				strs[i] = strs[j];
				strs[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int	ft_len_2d(char **strs)
{
	int	len;

	len = 0;
	while (strs[len])
		len++;
	return (len);
}

// int print_2d(char **strs)
// {
// 	int	i;

// 	i = 0;
// 	while (strs[i])
// 	{
// 		if (ft_strchr(strs[i], '='))
// 			printf("%s\n", strs[i]);
// 		i++;
// 	}
// }