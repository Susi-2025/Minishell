/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:15:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/15 15:41:02 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	printf_for_export(char *str);

int	exec_export(t_cmd *cmds, char **args, char ***temp_env)
{
	char	*args_heads;
	int		i;
	char	*value;
	int		equal_signal;
	
	if (args[1] == NULL)
		return (exec_export_only(cmds));
	i = 1;
	equal_signal = 0;
	while (args[i])
	{

		equal_signal = ft_strchr(args[i], '=');
		if ((args[i][0] >= '0' && args[i][0] <= '9') || args[i][0] == '_')
		{
			error_string_export(args[i]);
			return (1);
		}
		if (equal_signal)
			args_heads = ft_strhead(args[i], '=');
		else
			args_heads = args[i];
		if (check_var_env(*temp_env, args_heads) == 0)
		{
			if (insert_env(cmds, args[i], temp_env) == 1)
				return (1);
		}
		else if (equal_signal == 1 && check_var_env(*temp_env, args_heads) == 1)
		{
			value = ft_strtail(args[i], '=');
			update_env(cmds, args_heads, value);
			if (value)
				free(value);
		}
		if (equal_signal)
			free(args_heads);
		i++;
	}
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
		if (temp[i][0] != '_')
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
