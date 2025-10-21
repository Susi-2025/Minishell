/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:51:17 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/21 11:14:57 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	unsigned char	ch;

	len = 0;
	ch = (unsigned char) c;
	while (s[len])
		len++;
	if (ch == '\0')
		return ((char *)&s[len]);
	len--;
	while (len >= 0)
	{
		if ((unsigned char )s[len] == ch)
			return ((char *)&s[len]);
		len--;
	}
	return (NULL);
}
