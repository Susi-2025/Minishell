/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/21 21:13:40 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	check_n_cd(char *str);
static	void	echo_args(char *arg, int *stop_check, int *no_nl);

int	exec_echo(t_cmd *cmds, char **args, int args_count)
{
	int	i;
	int	no_nl;
	int	stop_check;

	if (!cmds)
		return (error_msg(1, "cmds"));
	if (args_count == 1)
    {
        printf("\n");
        return (0);
    }
	i = 1;
	no_nl = 0;
	stop_check = 0;
	while (args[i])
	{
		if (ft_strlen(args[i]) == 2 && ((args[i][0] == '\'' && args[i][1] == '\'')
			|| (args[i][0] == '"' && args[i][1] == '"')))
        {
            i++;
            continue; 
        }
		echo_args(args[i], &stop_check, &no_nl);
		if ((check_n_cd(args[i]) == 1) && (i < (args_count - 1)))
		{
			
			ft_printf_fd(STDIN_FILENO, " ");
		}
		i++;
	}
	if (no_nl == 0)
		printf("\n");
	return (0);
}

static	void	echo_args(char *arg, int *stop_check, int *no_nl)
{
	if (*stop_check == 0)
	{
		if (check_n_cd(arg) == 0)
		{
			*no_nl = 1;
			// *i++;
			return ;
		}
		else
		{
			*stop_check = 1;
			printf("%s", arg);
		}
	}
	else
		printf("%s", arg);
}

static	int	check_n_cd(char *str)
{
	int	i;
	
	if (!((str[0] == '-') && (str[1] == 'n')))
		return (1);
	i = 2;
	while (i < ft_strlen(str))
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}
