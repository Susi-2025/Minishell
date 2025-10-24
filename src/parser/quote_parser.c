/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:53:17 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/24 20:32:29 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_single_var(char *var, char *env[])
{
	int	i;
	int	len;

	i = 0;
	len = len_until_delim(var);
	while (env[i])
	{
		if (ft_strncmp(var, env[i], len) == 0 && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

static int	parse_dquote_dollar(t_expansion_state *st, char *line,
		t_expansion_context *ctx)
{
	st->i++;
	if (line[st->i] == '?')
	{
		st->final_str = ft_strjoin_and_free(st->final_str,
				ft_itoa(ctx->exit_code));
		if (!st->final_str)
			return (-1);
		st->i++;
	}
	else if (append_variable(&st->final_str, line, &st->i, ctx->env) == -1)
		return (-1);
	return (0);
}

static int	parse_dquote_loop(t_expansion_state *st, char *line,
		t_expansion_context *ctx)
{
	while (line[st->i] && line[st->i] != '\"')
	{
		if (line[st->i] == '$')
		{
			if (append_literal(&st->final_str, line, st->start, st->i) == -1)
				return (-1);
			if (parse_dquote_dollar(st, line, ctx) == -1)
				return (-1);
			st->start = st->i;
		}
		else
			st->i++;
	}
	return (0);
}

char	*free_final_str(char *final_str)
{
	error_syntax("\"");
	free(final_str);
	return (NULL);
}

char	*parse_dquote(char *line, int *j, t_expansion_context *ctx)
{
	t_expansion_state	st;

	st.i = 0;
	st.start = 0;
	st.final_str = ft_strdup("");
	if (!st.final_str)
		return (NULL);
	if (parse_dquote_loop(&st, line, ctx) == -1)
		return (free_final_str(st.final_str));
	if (line[st.i] == '\0')
		return (free_final_str(st.final_str));
	if (append_literal(&st.final_str, line, st.start, st.i) == -1)
		return (free_final_str(st.final_str));
	(*j) += st.i;
	return (st.final_str);
}
