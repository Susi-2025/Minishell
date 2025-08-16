/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:58:27 by vinguyen          #+#    #+#             */
/*   Updated: 2025/04/29 09:08:18 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*temp_s1;
	unsigned char	*temp_s2;

	i = 0;
	if (n == 0)
		return (0);
	temp_s1 = (unsigned char *)s1;
	temp_s2 = (unsigned char *)s2;
	while ((temp_s1[i]) && (temp_s2[i]) && (i < n))
	{
		if (temp_s1[i] != temp_s2[i])
			return (temp_s1[i] - temp_s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (temp_s1[i] - temp_s2[i]);
}
