/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/23 15:08:01 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	print_echo(char **args, int i);
static	int	is_valid_n_option(char *str);
static	int	detect_quote(char *str);

int	exec_echo(t_cmd *cmds, char **args, int args_count)
{
	if (!cmds)
		return (error_msg(1, "cmds"));
	if (args_count == 1)
	{
		printf("\n");
		return (0);
	}
	print_echo(args, 1);
	return (0);
}

static	void	print_echo(char **args, int i)
{
	int	no_nl;

	no_nl = 0;
	while (args[i] && is_valid_n_option(args[i]))
	{
		no_nl = 1;
		i++;
	}
	while (args[i])
	{
		if (!detect_quote(args[i]))
			printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!no_nl)
		printf("\n");
}

static	int	detect_quote(char *str)
{
	if (!str)
		return (0);
	if (ft_strlen(str) != 2)
		return (0);
	if ((ft_strcmp(str, "''") == 0) || (ft_strcmp(str, "\"\"") == 0))
		return (1);
	return (0);
}

static	int	is_valid_n_option(char *str)
{
	int	i;
	
	if (!str)
		return (0);
	if (!((str[0] == '-') && (str[1] == 'n')))
		return (0);
	i = 2;
	while (i < ft_strlen(str))
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
