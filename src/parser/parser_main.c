/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:27:52 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/14 19:15:56 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// static int	process_word_expansion(t_token *token,
		// t_simple_cmd **current_cmd,
// 		char *env[], int exit_code)
// {
// 	int		i;
// 	int		start;
// 	char	*final_cmd;
// 	char	*tmp;
// 	char	*str;
// 	int		var_start;
// 	int		var_len;
// 	char	*env_value;
// 	char	*var_name;

// 	i = 0;
// 	start = 0;
// 	final_cmd = ft_strdup(""); // Start with an empty, allocated string
// 	if (!final_cmd)
// 		return (ERROR);
// 	str = token->value;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 		{
// 			// 1. Append the unquoted part before this
// 			tmp = ft_substr(str, start, i - start);
// 			final_cmd = ft_strjoin_and_free(final_cmd, tmp);
// 			if (!final_cmd)
// 				return (MEM_ERROR);
// 			// 2. Find the closing quote and append the literal content
// 			i++; // Move past opening '
// 			start = i;
// 			while (str[i] && str[i] != '\'')
// 				i++;
// 			if (!str[i])
// 			{
// 				free(final_cmd);
// 				return (ERROR);
// 			}
// 			tmp = ft_substr(str, start, i - start);
// 			final_cmd = ft_strjoin_and_free(final_cmd, tmp);
// 			if (!final_cmd)
// 				return (MEM_ERROR);
// 			i++; // Move past closing '
// 			start = i;
// 		}
// 		else if (str[i] == '\"')
// 		{
// 			// 1. Append the unquoted part before this
// 			tmp = ft_substr(str, start, i - start);
// 			final_cmd = ft_strjoin_and_free(final_cmd, tmp);
// 			if (!final_cmd)
// 				return (MEM_ERROR);
// 			i++;
// 			tmp = parse_dquote(str + i, &i, env, exit_code);
// 			if (tmp == NULL)
// 			{
// 				free(final_cmd);
// 				return (ERROR);
// 			}
// 			final_cmd = ft_strjoin_and_free(final_cmd, tmp);
// 			if (!final_cmd)
// 				return (MEM_ERROR);
// 			i++; // Move past closing "
// 			start = i;
// 		}
// 		else if (str[i] == '$')
// 		{
// 			tmp = ft_substr(str, start, i - start);
// 			final_cmd = ft_strjoin_and_free(final_cmd, tmp);
// 			if (!final_cmd)
// 				return (MEM_ERROR);
// 			i++;
// 			var_start = i;
// 			var_len = len_until_delim(str + var_start);
// 			if (str[i] != '?' && var_len == 0)
// 				continue ;
// 			env_value = find_env_value(str + var_start, env, len_until_delim(str
// 						+ var_start));
// 			if (str[i] == '?')
// 			{
// 				final_cmd = ft_strjoin_and_free(final_cmd, ft_itoa(exit_code));
// 				if (!final_cmd)
// 					return (MEM_ERROR);
// 				i++;
// 			}
// 			else if (env_value == NULL || env_value[0] == '\0')
// 				free(env_value);
// 			else
// 			{
// 				var_name = ft_substr(str, var_start, len_until_delim(str
// 							+ var_start));
// 				if (!var_name)
// 				{
// 					free(env_value);
// 					free(final_cmd);
// 					return (MEM_ERROR);
// 				}
// 				final_cmd = handle_var_exp(final_cmd, env_value, current_cmd,
// 						var_name);
// 				free(var_name);
// 				if (!final_cmd)
// 					return (MEM_ERROR);
// 			}
// 			i = i + var_len;
// 			start = i;
// 		}
// 		else
// 			i++;
// 	}
// 	tmp = ft_substr(str, start, i - start);
// 	final_cmd = ft_strjoin_and_free(final_cmd, tmp);
// 	if (!final_cmd)
// 		return (MEM_ERROR);
// 	if (current_cmd != NULL && final_cmd[0] == '\0')
// 	{
// 		// If the final string is empty, we check if the *original*
// 		// token was an explicit quoted empty string.
// 		if (ft_strcmp(token->value, "\"\"") != 0 && ft_strcmp(token->value,
// 				"''") != 0)
// 		{
// 			// The original was NOT "" or ''.
// 			// It must have been an expansion like $non.
// 			// So, we discard it, just like bash.
// 			free(final_cmd);
// 			return (SUCCESS);
// 		}
// 		else
// 		{
// 			free(final_cmd);
// 			final_cmd = ft_strdup("''");
// 			if (!final_cmd)
// 				return (MEM_ERROR);
// 		}
// 		// If the original *was* "" or '', we fall through
// 		// and let it be added as a valid empty argument.
// 	}
// 	if (current_cmd == NULL)
// 	{
// 		free(token->value);
// 		token->value = final_cmd;
// 	}
// 	else
// 	{
// 		parse_word(final_cmd, current_cmd);
// 		free(final_cmd);
// 	}
// 	return (SUCCESS);
// }


static int	handle_redirection(t_token *tokens, int token_count, int *i,
		t_cmd *cmds)
{
	if (is_redirect_token(tokens[*i].type))
	{
		if (tokens[*i + 1].type != TOKEN_EOF && tokens[*i + 1].type == WORD)
		{
			if (process_word(&tokens[*i + 1], NULL, cmds->envp,
					cmds->err_code) != SUCCESS)
				return (ERROR);
		}
		return (parse_redir(tokens, token_count, i, cmds));
	}
	return (0);
}

static int	ensure_cmds_capacity(t_cmd *cmds)
{
	void	*tmp;

	if (cmds->cmds_count < cmds->cmds_capacity)
		return (0);
	tmp = ft_realloc(cmds->simple_cmds, sizeof(t_simple_cmd *)
			* cmds->cmds_capacity, sizeof(t_simple_cmd *) * cmds->cmds_capacity
			* 2);
	if (!tmp)
		return (-1);
	cmds->simple_cmds = tmp;
	cmds->cmds_capacity *= 2;
	return (0);
}

static t_simple_cmd	*init_simple_cmd(void)
{
	t_simple_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_simple_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args_capacity = 4;
	new_cmd->args_count = 0;
	new_cmd->args = malloc(sizeof(char *) * new_cmd->args_capacity);
	if (!new_cmd->args)
	{
		free(new_cmd);
		return (NULL);
	}
	new_cmd->args[0] = NULL;
	new_cmd->in_file = NULL;
	new_cmd->out_file = NULL;
	return (new_cmd);
}

int	create_current_cmd(t_simple_cmd **current_cmd, t_cmd *cmds)
{
	if (ensure_cmds_capacity(cmds) == -1)
		return (-1);
	*current_cmd = init_simple_cmd();
	if (!*current_cmd)
		return (-1);
	cmds->simple_cmds[cmds->cmds_count] = *current_cmd;
	cmds->cmds_count++;
	return (0);
}

static int	cmd_init(t_cmd *cmds, char *env[])
{
	cmds->cmds_capacity = 2;
	cmds->cmds_count = 0;
	cmds->heredoc_idx = 0;
	cmds->envp = env;
	cmds->err_file = NULL;
	cmds->file_append = NULL;
	cmds->simple_cmds = malloc(sizeof(t_simple_cmd *) * cmds->cmds_capacity);
	if (!cmds->simple_cmds)
		return (-1);
	return (0);
}

int	parse_tokens(t_cmd *cmds, t_token *tokens, int token_count, char *env[])
{
	int				i;
	t_simple_cmd	*current_cmd;

	if (cmd_init(cmds, env) == -1)
		return (ERROR);
	current_cmd = NULL;
	i = 0;
	while (i < token_count && tokens[i].type != TOKEN_EOF)
	{
		if (!current_cmd)
		{
			if (create_current_cmd(&current_cmd, cmds) == -1)
				return (ERROR);
		}
		if (process_word(&tokens[i], &current_cmd, env, cmds->err_code) == -1)
			return (ERROR);
		if (handle_redirection(tokens, token_count, &i, cmds) == -1)
			return (ERROR);
		if (tokens[i].type == PIPE)
			current_cmd = NULL;
		i++;
	}
	return (SUCCESS);
}
