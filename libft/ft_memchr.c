/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:44:35 by vinguyen          #+#    #+#             */
/*   Updated: 2025/04/28 15:03:22 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	c1;
	unsigned char	*s1;
	size_t			i;

	i = 0;
	c1 = (unsigned char)c;
	s1 = (unsigned char *)s;
	while (i < n)
	{
		if (s1[i] == c1)
			return ((void *)&s1[i]);
		i++;
	}
	return ((void *)0);
}
