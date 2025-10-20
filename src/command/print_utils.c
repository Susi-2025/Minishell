/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:33:06 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/20 10:33:41 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_for_export(char *str)
{
	int	i;

	ft_putstr_fd("declare -x ", STDIN_FILENO);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		write(STDIN_FILENO, &str[i], 1);
		i++;
	}
	if (str[i] == '=' && str[i + 1] != '\"' )
	{
		ft_putstr_fd("=\"", STDIN_FILENO);
		ft_putstr_fd(&str[i + 1], STDIN_FILENO);
		ft_putstr_fd("\"", STDIN_FILENO);
	}
	else
		ft_putstr_fd(&str[i], STDIN_FILENO);
	ft_putstr_fd("\n", STDIN_FILENO);
}
