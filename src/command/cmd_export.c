/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/15 17:28:17 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		invalid_args(char *str);
static	void	printf_for_export(char *str);

int	exec_export(t_cmd *cmds, char **args, char ***temp_env)
{
	// char	*args_heads;
	int		i;
	// char	*value;
	//int		equal_signal;
	
	if (args[1] == NULL)
		return (exec_export_only(cmds));
	i = 1;
	// equal_signal = 0;
	while (args[i])
	{
		//equal_signal = ft_strchr(args[i], '=');
		//if (args[i][0] >= '0' && args[i][0] <= '9')
		if (invalid_args(args[i]))
		{
			error_string_export(args[i]);
			i++;
		}
		if (export_with_args(cmds, args[i], temp_env) == 1)
			return (1);
		// if (ft_strchr(args[i], '='))
		// 	args_heads = ft_strhead(args[i], '=');
		// else
		// 	args_heads = args[i];
		// if (check_var_env(*temp_env, args_heads) == 0)
		// {
		// 	if (insert_env(cmds, args[i], temp_env) == 1)
		// 		return (1);
		// }
		// else if (ft_strchr(args[i], '=') == 1 && check_var_env(*temp_env, args_heads) == 1)
		// {
		// 	value = ft_strtail(args[i], '=');
		// 	if (update_env(cmds, args_heads, value) == 1)
		// 		return (1);
		// 	if (value)
		// 		free(value);
		// }
		// if (ft_strchr(args[i], '='))
		// 	free(args_heads);
		i++;
	}
	return (0);
}

// so [0] NOT number only alpha or _. the whole string alphanumeric or _ 
static	int	invalid_args(char *str)
{
	int	i;
	
	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
		return (1);
	i++;
	while (str[i])
	{
		if(ft_isalnum(str[i])== 0)
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
	out = malloc (i + 1);
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
	int len;
	char *out;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	i++;
	if (!str[i])
		return (NULL);
	len = ft_strlen(str) - i;
	out = malloc (len + 1);
	if (!out)
		return (NULL);
	j = 0;
	while (j < len)
	{
		if (str[i + j] == '\"')
			i++;
		out[j] = str[i + j];
		j++;
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
	while (temp[i])
	{
		// if (ft_strchr(temp[i], '=') && temp[i][0] != '_')
		if (temp[i][0] != '_') // not correct if we run export _viet => _viet must be added and showed
			printf_for_export(temp[i]);
		i++;
	}
	ft_free_triptr(&temp);
	return (0);
}

static	void	printf_for_export(char *str)
{
	int	i;

	printf("declare -x ");
	i = 0;
	while (str[i] && str[i] != '=')
	{
		printf("%c", str[i]);
		i++;
	}
	if (str[i] == '=' && str[i + 1] != '\"' )
	{
		printf("=\"%s\"", &str[i + 1]);
	}
	else
		printf("%s", &str[i]);
	printf("\n");
}
