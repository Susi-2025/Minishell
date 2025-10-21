/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_unsigned_fd.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:21:19 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/21 11:51:39 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_unsigned_fd(unsigned long long number, char *base,
		int i, int fd)
{
	int	res;

	res = 0;
	if (number / i > 0)
		res += ft_putnbr_base_unsigned_fd(number / i, base, i, fd);
	res += ft_putchar_fd(base[number % i], fd);
	return (res);
}
