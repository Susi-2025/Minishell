/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:10:33 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/24 20:45:30 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static unsigned int	count_int(long n)
{
	unsigned int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = n * (-1);
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	count;
	long			num;
	char			*out;

	num = n;
	count = count_int(num);
	out = (char *)malloc(count + 1);
	if (!out)
		return (0);
	if (num < 0)
	{
		num = num * (-1);
		out[0] = '-';
	}
	out[count] = '\0';
	if (num == 0)
		out[--count] = '0';
	while (num > 0)
	{
		out[--count] = num % 10 + '0';
		num = num / 10;
	}
	return (out);
}
