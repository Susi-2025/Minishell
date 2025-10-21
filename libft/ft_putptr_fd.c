/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:56:58 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/21 11:57:17 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_fd(void *ptr, char *base, int i, int fd)
{
	int					res;
	unsigned long long	add;

	res = 0;
	add = (unsigned long long)ptr;
	if (add == 0)
		return (ft_putstr_fd_v("(nil)", fd));
	res += ft_putstr_fd_v("0x", fd);
	res += ft_putnbr_base_unsigned_fd(add, base, i, fd);
	return (res);
}
