/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:06:28 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/24 17:06:42 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	is_space(char c)
{
	int		i;
	char	*spaces;

	spaces = " \t\r\n\v";
	i = 0;
	while (spaces[i])
	{
		if (c == spaces[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_delimiter(char c)
{
	int		i;
	char	*delimiters;

	delimiters = "|<>";
	i = 0;
	while (delimiters[i])
	{
		if (c == delimiters[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z' ));
}

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}


int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}