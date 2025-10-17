/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:54:14 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/17 12:54:23 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_and_free(char **output, char *input)
{
	char	*res;
	char	*ptr;
	int		i;

	res = (char *)malloc(ft_strlen(*output) + ft_strlen(input) + 2);
	if (!res)
		return (1);
	ptr = res;
	i = 0;
	while (*output && (*output)[i])
		*ptr++ = (*output)[i++];
	i = 0;
	while (input && input[i])
		*ptr++ = input[i++];
	*ptr++ = '\n';
	*ptr = '\0';
	if (*output)
		free(*output);
	if (input)
		free(input);
	*output = res;
	return (0);
}
