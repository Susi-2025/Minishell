/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:59:59 by vinguyen          #+#    #+#             */
/*   Updated: 2025/04/28 18:23:41 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	size_t			check_overflow;
	unsigned char	*ptr;

	i = 0;
	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(1);
		*ptr = '\0';
		return (ptr);
	}
	check_overflow = nmemb * size;
	if (check_overflow / nmemb != size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (i < (nmemb * size))
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
