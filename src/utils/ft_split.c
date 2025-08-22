/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:05:24 by cdohanic          #+#    #+#             */
/*   Updated: 2025/04/27 17:20:15 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	is_separator(char c, char delimiter)
{
	return (c == delimiter || c == '\0');
}

int	count_strings(char const *str, char delimiter)
{
	int	strings;
	int	i;

	strings = 0;
	i = 0;
	while (str[i])
	{
		if (is_separator(str[i + 1], delimiter)
			&& !(is_separator(str[i], delimiter)))
			strings++;
		i++;
	}
	return (strings);
}

static void	ft_write_string(char *dest, char const *src, char c)
{
	int	i;

	i = 0;
	while (!(is_separator(src[i], c)))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static void	ft_write_arrays(char **result, char const *str, char delimiter)
{
	int	i;
	int	j;
	int	word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (is_separator(str[i], delimiter))
			i++;
		else
		{
			j = 0;
			while (!is_separator(str[i + j], delimiter))
				j++;
			result[word] = (char *)malloc(sizeof(char) * (j + 1));
			ft_write_string(result[word], str + i, delimiter);
			i += j;
			word++;
		}
	}
}

char	**ft_split(char const *str, char c)
{
	char	**result;
	int		str_count;

	if (str == NULL)
		return (NULL);
	str_count = count_strings(str, c);
	result = (char **)malloc(sizeof(char *) * (str_count + 1));
	if (!result)
		return (NULL);
	result[str_count] = NULL;
	ft_write_arrays(result, str, c);
	return (result);
}
