/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/16 14:12:02 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		invalid_args(char *str);
static	void	printf_for_export(char *str);

int	exec_export(t_cmd *cmds, char **args, char ***temp_env)
{
	int		i;
	
	if (args[1] == NULL)
		return (exec_export_only(cmds));
	i = 1;
	while (args[i])
	{
		if (invalid_args(args[i]))
		{
			error_string_export(args[i]);
			i++;
		}
		if (export_with_args(cmds, args[i], temp_env) == 1)
			return (1);
		i++;
	}
	return (0);
}
// so [0] NOT number only alpha or _. the whole string alphanumeric or _ 
static	int	invalid_args(char *str)
{
	int	i;
	
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (1);
	i = 1;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '=' || str[i] == '"'))
			return (1);
		i++;
	}
	return (0);
}

int export_with_args(t_cmd *cmds, char *arg_str, char ***temp_env)
{
	char	*args_heads;
	char	*value;
	
	if (ft_strchr(arg_str, '='))
		args_heads = ft_strhead(arg_str, '=');
	else
		args_heads = arg_str;
	if (check_var_env(*temp_env, args_heads) == 0)
	{
		if (insert_env(cmds, arg_str, temp_env) == 1)
			return (1);
	}
	else if (ft_strchr(arg_str, '=') == 1 && check_var_env(*temp_env, args_heads) == 1)
	{
		value = ft_strtail(arg_str, '=');
		printf("Value is: %s\n", value);
		if (update_env(cmds, args_heads, value) == 1)
			return (1);
		if (value)
			free(value);
	}
	if (ft_strchr(arg_str, '='))
		free(args_heads);
	return (0);
}

char	*ft_strhead(char *str, char c)
{
	int	i;
	int j;
	char *out;

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
	int	i;
	int j;
	char *out;

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

int	exec_export_only(t_cmd *cmds)
{
	int		i;
	char	**temp;

	if (!cmds->envp)
		return (error_msg(1, "envp"));
	i = 0;
	temp = ft_matrix_dup(cmds->envp, ft_len_2d(cmds->envp));
	if (!temp)
		return (1);
	sort_2d_array(temp);
	while (i < ft_len_2d(temp))
	{
		if (temp[i][0] == '_' && temp[i][1] == '=')
			i++;
		if (temp[i] && i < ft_len_2d(temp))
			printf_for_export(temp[i]);
		i++;
	}
	ft_free_triptr(&temp);
	return (0);
}

static	void	printf_for_export(char *str)
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
