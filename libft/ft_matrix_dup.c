/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:08:00 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/23 11:13:17 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matrix_dup(char **matrix, int row)
{
	char	**out;
	int		i;

	out = (char **)ft_calloc(row + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	while (i < row)
	{
		out[i] = ft_strdup(matrix[i]);
		if (!out[i])
		{
			ft_free_triptr(&out);
			return (NULL);
		}
		i++;
	}
	return (out);
}
