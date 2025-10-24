/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:45:39 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:27 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			set_exit_code(char *s);
static int			is_overflow(const char *str);
static long long	ft_atoll(const char *str);

int	exec_exit(t_cmd *cmds, char *s, char **temp_env, int args_count)
{
	int	status;

	status = cmds->err_code;
	dup_std(cmds->orig_stdin, cmds->orig_stdout);
	if (args_count > 2)
	{
		if (ft_is_numeric(s) == 0)
		{
			printf("exit\n");
			status = error_cmd_fd(2, "exit", s, NUM_ARG);
			free_and_exit(cmds, temp_env, status);
		}
		else
			return (error_cmd_fd(1, "exit", "", MANY_ARGS));
	}
	else
	{
		if (cmds->cmds_count == 1)
			printf("exit\n");
		status = set_exit_code(s);
		free_and_exit(cmds, temp_env, status);
	}
	return (status);
}

static int	set_exit_code(char *s)
{
	long long	num;
	int			status;

	if (!s)
		return (0);
	if (s && ft_is_numeric(s) == 0)
		return (error_cmd_fd(2, "exit", s, NUM_ARG));
	if (is_overflow(s))
		return (error_cmd_fd(2, "exit", s, NUM_ARG));
	num = ft_atoll(s);
	status = (int)(num & 255);
	return (status);
}

static int	is_overflow(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	num;
	unsigned long long	digit;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i++] - '0';
		if (num > LLONG_MAX / 10
			|| (num == LLONG_MAX / 10
				&& digit > (unsigned long long)(LLONG_MAX % 10)))
			return (1);
		num = num * 10 + digit;
	}
	if (sign == -1 && num > (unsigned long long)LLONG_MAX + 1)
		return (1);
	return (0);
}

static long long	ft_atoll(const char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}
