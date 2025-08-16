/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:47:43 by vinguyen          #+#    #+#             */
/*   Updated: 2025/04/29 12:07:44 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static unsigned int	ft_count(const char *s, char c)
{
	unsigned int	start;
	unsigned int	len;
	unsigned int	count_word;
	unsigned int	i;

	start = 0;
	len = ft_strlen(s);
	count_word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			start = 1;
		if ((start > 0) && ((s[i] == c) || (i == (len - 1))))
			start = 2;
		if (start == 2)
		{
			count_word++;
			start = 0;
		}
		i++;
	}
	return (count_word);
}

static char	*ft_assign(char *s, char c)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	i;
	char			*out_sub;

	i = 0;
	while (s[i] == c)
		i++;
	start = i;
	while ((s[i] != c) && (s[i] != '\0'))
		i++;
	end = i;
	i = 0;
	out_sub = (char *)malloc(end - start + 1);
	if (!out_sub)
		return (NULL);
	while (start < end)
	{
		out_sub[i] = s[start];
		i++;
		start++;
	}
	out_sub[i] = '\0';
	return (out_sub);
}

static void	ft_free(char **s, int n)
{
	while (n >= 0)
	{
		free (s[n]);
		n--;
	}
	free (s);
}

char	**ft_split(char const *s, char c)
{
	char			**out;
	char			*s_temp;
	unsigned int	count;
	unsigned int	i;

	i = 0;
	count = ft_count(s, c);
	s_temp = (char *)s;
	out = (char **)malloc(sizeof(char *) * (count + 1));
	if (!out)
		return (0);
	while (i < count && s_temp)
	{
		while (*s_temp == c)
			s_temp++;
		if (*s_temp == '\0')
			break ;
		out[i] = ft_assign(s_temp, c);
		if (out[i] == NULL)
			ft_free(out, i - 1);
		s_temp = s_temp + ft_strlen(out[i]) + 1;
		i++;
	}
	out[i] = NULL;
	return (out);
}
