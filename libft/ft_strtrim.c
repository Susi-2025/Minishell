/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:04:20 by vinguyen          #+#    #+#             */
/*   Updated: 2025/04/28 21:49:05 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	k;
	char			*out;

	start = 0;
	while (str[start] && ft_strchr(set, str[start]))
		start++;
	end = ft_strlen(str);
	while (end > start && ft_strrchr(set, str[end - 1]))
		end--;
	out = (char *)malloc(end - start + 1);
	if (!out)
		return (NULL);
	k = 0;
	while (start < end)
	{
		out[k] = str[start];
		start++;
		k++;
	}
	out[k] = '\0';
	return (out);
}
