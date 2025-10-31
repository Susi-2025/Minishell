/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:16:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/21 11:56:22 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdarg.h"

static	int	check_string_fd(va_list args, const char *string, int i, int fd);
static	int	check_format_fd(va_list args, const char *string, int i, int fd);

int	ft_printf_fd(int fd, const char *string, ...)
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
		if (string[i] == '%' && ft_strchr_char("%", string[i + 1]))
			i++;
		else if (string[i] == '%' && !ft_strchr_char("cspdiuxX", string[i + 1]))
			return (-1);
		i++;
	}
	i = 0;
	new_out = check_string_fd(args, string, i, fd);
	va_end (args);
	return (new_out);
}

static	int	check_string_fd(va_list args, const char *string, int i, int fd)
{
	int	new_out;
	int	out;

	out = 0;
	new_out = 0;
	while (string[i])
	{
		if (string[i] != '%')
			out += ft_putchar_fd(string[i], fd);
		else
		{
			out += check_format_fd(args, string, i + 1, fd);
			i++;
		}
		if (new_out > out)
			return (-1);
		new_out = out;
		i++;
	}
	return (new_out);
}

static	int	check_format_fd(va_list args, const char *string, int i, int fd)
{
	char	*hex;
	char	*hex_up;

	hex = "0123456789abcdef";
	hex_up = "0123456789ABCDEF";
	if (string[i] == 'c')
		return (ft_putchar_fd((char)va_arg(args, int), fd));
	else if (string[i] == 's')
		return (ft_putstr_fd_v((char *)va_arg(args, char *), fd));
	else if (string[i] == 'p')
		return (ft_putptr_fd(va_arg(args, void *), hex, 16, fd));
	else if (string[i] == 'd' || string[i] == 'i')
		return (ft_putnbr_base_fd(va_arg(args, int), hex, 10, fd));
	else if (string[i] == 'u')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int), hex, 10, fd));
	else if (string[i] == 'x')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int), hex, 16, fd));
	else if (string[i] == 'X')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int), hex_up, 16, fd));
	else if (string[i] == '%')
		return (ft_putchar_fd('%', fd));
	else
		return (-1);
}
