/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:23:21 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/23 11:13:35 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(long long number, char *base, int i)
{
	int					res;
	unsigned long long	new_no;

	res = 0;
	if (number < 0)
	{
		new_no = (unsigned long long)(-number);
		res += ft_putchar('-');
	}
	else
		new_no = (unsigned long long)(number);
	if (new_no / i > 0)
		res += ft_putnbr_base(new_no / i, base, i);
	res += ft_putchar(base[new_no % i]);
	return (res);
}
