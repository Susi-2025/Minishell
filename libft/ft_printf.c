/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:16:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/23 11:13:24 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		i;
	int		new_out;

	if (!string)
		return (-1);
	i = 0;
	va_start (args, string);
	while (string[i])
	{
		if (string[i] == '%' && ft_strchr("%", string[i + 1]))
			i++;
		else if (string[i] == '%' && !ft_strchr("cspdiuxX", string[i + 1]))
			return (-1);
		i++;
	}
	i = 0;
	new_out = check_string(args, string, i);
	va_end (args);
	return (new_out);
}

int	check_string(va_list args, const char *string, int i)
{
	int	new_out;
	int	out;

	out = 0;
	new_out = 0;
	while (string[i])
	{
		if (string[i] != '%')
			out += ft_putchar(string[i]);
		else
		{
			out += check_format(args, string, i + 1);
			i++;
		}
		if (new_out > out)
			return (-1);
		new_out = out;
		i++;
	}
	return (new_out);
}

int	check_format(va_list args, const char *string, int i)
{
	char	*hex;
	char	*hex_up;

	hex = "0123456789abcdef";
	hex_up = "0123456789ABCDEF";
	if (string[i] == 'c')
		return (ft_putchar((char)va_arg(args, int)));
	else if (string[i] == 's')
		return (ft_putstr((char *)va_arg(args, char *)));
	else if (string[i] == 'p')
		return (ft_putptr(va_arg(args, void *), hex, 16));
	else if (string[i] == 'd' || string[i] == 'i')
		return (ft_putnbr_base(va_arg(args, int), hex, 10));
	else if (string[i] == 'u')
		return (ft_putnbr_base(va_arg(args, unsigned int), hex, 10));
	else if (string[i] == 'x')
		return (ft_putnbr_base(va_arg(args, unsigned int), hex, 16));
	else if (string[i] == 'X')
		return (ft_putnbr_base(va_arg(args, unsigned int), hex_up, 16));
	else if (string[i] == '%')
		return (ft_putchar('%'));
	else
		return (-1);
}
