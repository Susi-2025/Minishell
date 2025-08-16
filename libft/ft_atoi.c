/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:47:19 by vinguyen          #+#    #+#             */
/*   Updated: 2025/04/28 22:44:42 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	sign_check(char **str1)
{
	int	sign;

	sign = 1;
	if (**str1 == '-')
	{
		sign = -1;
		(*str1)++;
	}
	else if (**str1 == '+')
	{
		sign = 1;
		(*str1)++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		res;
	char	*str1;

	sign = 1;
	res = 0;
	str1 = (char *)str;
	while ((*str1 >= 9 && *str1 <= 13) || (*str1 == 32))
		str1++;
	sign = sign_check(&str1);
	if (!((*str1 >= '0') && (*str1 <= '9')))
		return (0);
	while ((*str1 >= '0') && (*str1 <= '9'))
	{
		res = res * 10 + (*str1 - '0');
		str1++;
	}
	res = res * sign;
	return (res);
}
