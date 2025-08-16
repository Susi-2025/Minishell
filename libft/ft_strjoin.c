/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:46:53 by vinguyen          #+#    #+#             */
/*   Updated: 2025/04/22 14:57:18 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*out;

	i = -1;
	len1 = 0;
	len2 = 0;
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	out = (char *)malloc(len1 + len2 + 1);
	if (!out)
		return (NULL);
	while (++i < len1)
		out[i] = s1[i];
	i = -1;
	while (++i < len2)
		out[len1 + i] = s2[i];
	out[len1 + i] = '\0';
	return (out);
}
