/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_unsigned.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:21:19 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/23 11:13:31 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_unsigned(unsigned long long number, char *base, int i)
{
	int	res;

	res = 0;
	if (number / i > 0)
		res += ft_putnbr_base_unsigned (number / i, base, i);
	res += ft_putchar(base[number % i]);
	return (res);
}
