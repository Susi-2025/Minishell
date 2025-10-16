/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/16 17:00:26 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_cmp_strs(char *s1, char *s2);

void	sort_2d_array(char **strs)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	i = 0;
	len = ft_len_2d(strs);
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_cmp_strs(strs[i], strs[j]) > 0)
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

static	int	ft_cmp_strs(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if ((s1[i] == '=' || s1[i] == '\0') && (s2[i] == '=' || s2[i] == '\0'))
		return (ft_strcmp(s1, s2));
	if (s1[i] == '=' || s1[i] == '\0')
		return (-1);
	else
		return (1);
}
