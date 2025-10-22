/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:55:53 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/22 16:55:53 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_single_quote(t_expansion_state *st, char *str)
{
	char	*tmp;

	tmp = ft_substr(str, st->start, st->i - st->start);
	st->final_str = ft_strjoin_and_free(st->final_str, tmp);
	if (!st->final_str)
		return (MEM_ERROR);
	st->i++;
	st->start = st->i;
	while (str[st->i] && str[st->i] != '\'')
		st->i++;
	if (!str[st->i])
	{
		free(st->final_str);
		return (ERROR);
	}
	tmp = ft_substr(str, st->start, st->i - st->start);
	st->final_str = ft_strjoin_and_free(st->final_str, tmp);
	if (!st->final_str)
		return (MEM_ERROR);
	st->i++;
	st->start = st->i;
	return (SUCCESS);
}

int	handle_double_quote(t_expansion_state *st, char *str,
		t_expansion_context *ctx)
{
	char	*tmp;

	tmp = ft_substr(str, st->start, st->i - st->start);
	st->final_str = ft_strjoin_and_free(st->final_str, tmp);
	if (!st->final_str)
		return (MEM_ERROR);
	st->i++;
	tmp = parse_dquote(str + st->i, &st->i, ctx);
	if (tmp == NULL)
	{
		free(st->final_str);
		return (ERROR);
	}
	st->final_str = ft_strjoin_and_free(st->final_str, tmp);
	if (!st->final_str)
		return (MEM_ERROR);
	st->i++;
	st->start = st->i;
	return (SUCCESS);
}

int	var_expansion_helper(char *env_value, t_expansion_state *st,
	char *str, t_expansion_context *ctx)
{
	char	*var_name;
	int		var_len;

	var_len = len_until_delim(str + st->i);
	var_name = ft_substr(str, st->i, var_len);
	if (!var_name)
	{
		free(env_value);
		return (MEM_ERROR);
	}
	st->final_str = handle_var_exp(st->final_str, env_value,
			ctx->current_cmd, var_name);
	free(var_name);
	st->i += var_len;
	if (!st->final_str)
		return (MEM_ERROR);
	return (SUCCESS);
}

int	handle_regular_var(t_expansion_state *st, char *str,
		t_expansion_context *ctx)
{
	int		var_len;
	char	*env_value;

	var_len = len_until_delim(str + st->i);
	if (var_len == 0)
	{
		st->final_str = ft_strjoin_and_free(st->final_str, ft_strdup("$"));
		if (!st->final_str)
			return (MEM_ERROR);
		return (SUCCESS);
	}
	env_value = find_env_value(str + st->i, ctx->env, var_len);
	if (env_value == NULL || env_value[0] == '\0')
	{
		free(env_value);
		st->i += var_len;
		return (SUCCESS);
	}
	else
		return (var_expansion_helper(env_value, st, str, ctx));
}

int	handle_dollar_expansion(t_expansion_state *st, char *str,
		t_expansion_context *ctx)
{
	char	*tmp;

	tmp = ft_substr(str, st->start, st->i - st->start);
	st->final_str = ft_strjoin_and_free(st->final_str, tmp);
	if (!st->final_str)
		return (MEM_ERROR);
	st->i++;
	if (str[st->i] == '?')
	{
		st->final_str = ft_strjoin_and_free(st->final_str,
				ft_itoa(ctx->exit_code));
		if (!st->final_str)
			return (MEM_ERROR);
		st->i++;
	}
	else if (handle_regular_var(st, str, ctx) == MEM_ERROR)
		return (MEM_ERROR);
	st->start = st->i;
	return (SUCCESS);
}
