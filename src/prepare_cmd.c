/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:58:39 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/23 14:42:42 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*handle_tokenization(char *line, int *token_count, t_cmd *cmds)
{
	t_token	*tokens;

	tokens = tokenize(line, token_count);
	if (!tokens)
	{
		vector_destroy(cmds->heredoc_files);
		free(cmds);
		return (NULL);
	}
	return (tokens);
}

static int	handle_syntax_checking(t_token *tokens, int token_count,
		t_cmd *cmds)
{
	if (syntax_checker(tokens, token_count, cmds) == ERROR)
	{
		free_tokens(tokens, token_count);
		vector_destroy_heredocs(cmds->heredoc_files);
		free(cmds);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	handle_parsing(t_cmd *cmds, t_token *tokens, int token_count,
		char *env[])
{
	if (parse_tokens(cmds, tokens, token_count, env) == ERROR)
	{
		free_tokens(tokens, token_count);
		free_cmd(cmds);
		return (ERROR);
	}
	return (SUCCESS);
}

static t_cmd	*init_cmd_struct(char *env[], int error_code)
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	cmds->err_code = error_code;
	cmds->orig_stdin = -1;
	cmds->orig_stdout = -1;
	cmds->envp = env;
	cmds->heredoc_files = malloc(sizeof(t_vector));
	if (!cmds->heredoc_files)
	{
		free(cmds);
		return (NULL);
	}
	if (vector_setup(cmds->heredoc_files) == VECTOR_ERROR)
	{
		free(cmds->heredoc_files);
		free(cmds);
		return (NULL);
	}
	return (cmds);
}

t_cmd	*ft_prepare_command(char *line, char *env[], int error_code)
{
	int		token_count;
	t_token	*tokens;
	t_cmd	*cmds;

	cmds = init_cmd_struct(env, error_code);
	if (!cmds)
		return (NULL);
	tokens = handle_tokenization(line, &token_count, cmds);
	if (!tokens)
		return (NULL);
	if (handle_syntax_checking(tokens, token_count, cmds) == ERROR)
		return (NULL);
	if (handle_parsing(cmds, tokens, token_count, env) == ERROR)
		return (NULL);
	free_tokens(tokens, token_count);
	return (cmds);
}
