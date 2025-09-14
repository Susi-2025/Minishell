/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_err_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:02:33 by vinguyen          #+#    #+#             */
/*   Updated: 2025/09/08 11:24:48 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_malloc(t_cmd *cmds, int code)
{
	free_cmd(cmds);
	return (code);
}

int	error_msg(int code, char *str)
{
	printf("%s\n", str);
	return (code);
}
