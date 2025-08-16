/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:17:31 by vinguyen          #+#    #+#             */
/*   Updated: 2025/04/29 10:20:20 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[i] == '\0')
		return ((char *)&big[i]);
	if (len == 0)
		return (NULL);
	while (big[i] && (i < len))
	{
		if (big[i] == little[j])
		{
			while ((big[i + j] == little[j]) && little[j] && ((i + j) < len))
				j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
			j = 0;
		}
		i++;
	}
	return (NULL);
}
