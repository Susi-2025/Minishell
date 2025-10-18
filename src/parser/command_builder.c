/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:50:32 by cdohanic          #+#    #+#             */
/*   Updated: 2025/09/22 09:47:14 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	parse_word(char *word, t_simple_cmd **current_cmd)
{
	void	*tmp;

	if (word == NULL)
		return (-1);
	if ((*current_cmd)->args_count >= (*current_cmd)->args_capacity - 1)
	{
		tmp = ft_realloc((*current_cmd)->args, sizeof(char *) * (*current_cmd)->args_capacity, sizeof(char *)
				* (*current_cmd)->args_capacity * 2);
		if (!tmp)
			return (-1);
		(*current_cmd)->args_capacity *= 2;
		(*current_cmd)->args = tmp;
	}
	(*current_cmd)->args[(*current_cmd)->args_count] = ft_strdup(word);
	if ((*current_cmd)->args[(*current_cmd)->args_count] == NULL)
		return (-1);
	(*current_cmd)->args_count++;
	(*current_cmd)->args[(*current_cmd)->args_count] = NULL;
	return (0);
}
