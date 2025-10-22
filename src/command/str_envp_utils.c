/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_envp_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/22 14:34:52 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_args(char *str)
{
	int	i;
	int	invalid;

	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (1);
	i = 1;
	invalid = 0;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '"'
				|| str[i] == '\'' || str[i] == '_'))
			invalid++;
		i++;
	}
	if (invalid == 1)
	{
		if (str[i - 1] == '+' && str[i] == '=')
			invalid = 0;
	}
	else if (invalid > 1)
		invalid = 1;
	return (invalid);
}

char	*ft_strhead(char *str, char c)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	out = malloc(i + 1);
	if (!out)
		return (NULL);
	j = 0;
	while (j < i)
	{
		out[j] = str[j];
		j++;
	}
	out[j] = '\0';
	return (out);
}

char	*ft_strtail(char *str, char c)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	i++;
	out = malloc(ft_strlen(str) - i + 1);
	if (!out)
		return (NULL);
	j = 0;
	while (str[i])
	{
		if (str[i] != '\"')
			out[j++] = str[i];
		i++;
	}
	out[j] = '\0';
	return (out);
}

char	*create_new_str(char *key, char *value)
{
	char	*new_str;
	int		len_key;
	int		len_value;

	len_key = ft_strlen(key);
	if (value == NULL)
		len_value = 0;
	else
		len_value = ft_strlen(value);
	new_str = malloc(sizeof(char) * (len_key + len_value + 2));
	if (!new_str)
		return (NULL);
	ft_copy_str(new_str, key, value);
	return (new_str);
}

void	ft_copy_str(char *origin, char *key, char *value)
{
	int	j;
	int	k;

	j = 0;
	while (key[j])
	{
		origin[j] = key[j];
		j++;
	}
	origin[j++] = '=';
	k = 0;
	if (value)
	{
		while (value[k])
			origin[j++] = value[k++];
	}
	origin[j] = '\0';
}
