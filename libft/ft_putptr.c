/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:56:58 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/23 11:13:42 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(void *ptr, char *base, int i)
{
	int					res;
	unsigned long long	add;

	res = 0;
	add = (unsigned long long)ptr;
	if (add == 0)
		return (ft_putstr("(nil)"));
	res += ft_putstr("0x");
	res += ft_putnbr_base_unsigned(add, base, i);
	return (res);
}
