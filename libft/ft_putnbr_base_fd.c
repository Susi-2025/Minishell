/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:23:21 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/21 11:58:16 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_fd(long long number, char *base, int i, int fd)
{
	int					res;
	unsigned long long	new_no;

	res = 0;
	if (number < 0)
	{
		new_no = (unsigned long long)(-number);
		res += ft_putchar_fd('-', fd);
	}
	else
		new_no = (unsigned long long)(number);
	if (new_no / i > 0)
		res += ft_putnbr_base_fd(new_no / i, base, i, fd);
	res += ft_putchar_fd(base[new_no % i], fd);
	return (res);
}
