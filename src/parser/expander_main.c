/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:55:42 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/24 20:33:22 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_expansion_loop(t_expansion_state *st, char *str,
		t_expansion_context *ctx)
{
	int	status;

	while (str[st->i])
	{
		if (str[st->i] == '\'')
			status = handle_single_quote(st, str);
		else if (str[st->i] == '\"')
			status = handle_double_quote(st, str, ctx);
		else if (str[st->i] == '$')
			status = handle_dollar_expansion(st, str, ctx);
		else
		{
			st->i++;
			status = SUCCESS;
		}
		if (status != SUCCESS)
			return (status);
	}
	return (SUCCESS);
}

static int	handle_empty_expansion(char **final_cmd_ptr, t_token *token)
{
	char	*final_cmd;

	final_cmd = *final_cmd_ptr;
	if (ft_strcmp(token->value, "\"\"") != 0 && ft_strcmp(token->value,
			"''") != 0)
	{
		free(final_cmd);
		*final_cmd_ptr = NULL;
		return (DISCARD_TOKEN);
	}
	else
	{
		free(final_cmd);
		*final_cmd_ptr = ft_strdup("''");
		if (!*final_cmd_ptr)
			return (MEM_ERROR);
		return (SUCCESS);
	}
}

static int	finalize_expansion(char *final_cmd, t_token *token,
		t_simple_cmd **current_cmd)
{
	int	result;

	if (current_cmd != NULL && final_cmd[0] == '\0')
	{
		result = handle_empty_expansion(&final_cmd, token);
		if (result == DISCARD_TOKEN)
			return (SUCCESS);
		if (result == MEM_ERROR)
			return (MEM_ERROR);
	}
	if (current_cmd == NULL)
	{
		free(token->value);
		token->value = final_cmd;
	}
	else
	{
		parse_word(final_cmd, current_cmd);
		free(final_cmd);
	}
	return (SUCCESS);
}

int	process_word_expansion(t_token *token, t_simple_cmd **current_cmd,
		char *env[], int exit_code)
{
	t_expansion_state	st;
	t_expansion_context	ctx;
	char				*tmp;
	int					status;

	st.i = 0;
	st.start = 0;
	st.final_str = ft_strdup("");
	if (!st.final_str)
		return (ERROR);
	ctx.env = env;
	ctx.exit_code = exit_code;
	ctx.current_cmd = current_cmd;
	status = process_expansion_loop(&st, token->value, &ctx);
	if (status != SUCCESS)
		return (status);
	tmp = ft_substr(token->value, st.start, st.i - st.start);
	st.final_str = ft_strjoin_and_free(st.final_str, tmp);
	if (!st.final_str)
		return (MEM_ERROR);
	return (finalize_expansion(st.final_str, token, current_cmd));
}

int	process_word(t_token *token, t_simple_cmd **current_cmd,
		char *env[], int exit_status)
{
	int	return_num;

	if (token->type == WORD)
	{
		return_num = process_word_expansion(token, current_cmd, env,
				exit_status);
		if (return_num == MEM_ERROR)
		{
			printf("minishell: memory error\n");
			return (ERROR);
		}
		else if (return_num == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
