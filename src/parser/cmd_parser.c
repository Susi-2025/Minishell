/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:27:52 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/22 11:37:45 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	cmd_init(t_cmd *cmds)
{
    cmds->cmds_capacity = 2;
    cmds->cmds_count = 0;
    cmds->in_file = NULL;
    cmds->out_file = NULL;
    cmds->err_file = NULL;
    cmds->here_doc = NULL;
    cmds->file_append = NULL;
	cmds->simple_cmds = malloc(sizeof(t_simple_cmd *) * cmds->cmds_capacity);
    if (!cmds->simple_cmds)
		return (-1);
	return (0);
}

//NEW_STUFF
int	len_until_delim(char *word)
{
	int	i;

	if (!word)
		return (0);
	i = 0;
	while (word[i] && ft_isalnum(word[i]))
		i++;
	return (i);
}

int	find_dollar_pos(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
		return (i);
	return (-1);
}

char	*find_env_value(char *variable, char *env[], int var_len)
{
	int	i;

	if (!variable || !env || var_len <= 0)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		if (env[i] && ft_strncmp(variable, env[i], var_len) == 0 && env[i][var_len] == '=')
			return (ft_strdup(env[i] + var_len + 1));
		i++;
	}
	return (ft_strdup(""));
}

int	handle_prefix(char **result, char *line, int dollar_pos)
{
	char	*prefix;
	char	*temp;

	if (dollar_pos <= 0)
		return (1);
	prefix = ft_substr(line, 0, dollar_pos);
	if (!prefix)
		return (0);
	temp = ft_strjoin(prefix, result[0]);
	free(prefix);
	if (!temp)
		return (0);
	free(result[0]);
	result[0] = temp;
	return (1);
}

int	handle_suffix(char **result, char *variable, int var_len)
{
	char	*temp;
	int		last_idx;

	if (ft_strlen(variable) <= var_len)
		return (1);
	last_idx = 0;
	while (result[last_idx])
		last_idx++;
	if (last_idx == 0)
		return (1);
	last_idx--;
	temp = ft_strjoin(result[last_idx], variable + var_len);
	if (!temp)
		return (0);
	free(result[last_idx]);
	result[last_idx] = temp;
	return (1);
}

char	**process_expansion(char *line, char *env[], int dollar_pos)
{
	char	*variable;
	char	**result;
	char	*env_value;
	int		var_len;

	variable = line + dollar_pos + 1;
	var_len = len_until_delim(variable);
	env_value = find_env_value(variable, env, var_len);
	if (!env_value)
		return (NULL);
	//MODIFY FT_SPLIT TO USE IS_SPACE INSTEAD OF ' '
	result = ft_split(env_value, ' ');
	free(env_value);
	if (!result)
		return (NULL);
	if (!handle_prefix(result, line, dollar_pos))
		return (free_split(result), NULL);
	if (!handle_suffix(result, variable, var_len))
		return (free_split(result), NULL);
	return (result);
}

char	**expand_var(char *line_value, char *env[])
{
	int		dollar_pos;

	if (!env || !line_value)
		return (NULL);
	dollar_pos = find_dollar_pos(line_value);
	if (dollar_pos == -1)
		return (NULL);
	return (process_expansion(line_value, env, dollar_pos));
}

char    *expand_single_var(char *var, char *env[])
{
	int     i;
	int     len;

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

static int	append_literal(char **result, char *line, int start, int end)
{
	char	*literal;
	char	*temp;

	if (start >= end)
		return (0);
	literal = ft_substr(line, start, end - start);
	if (!literal)
		return (free(*result), -1);
	temp = ft_strjoin(*result, literal);
	free(literal);
	if (!temp)
		return (free(*result), -1);
	free(*result);
	*result = temp;
	return (0);
}

static int	append_variable(char **result, char *line, int *i, char *env[])
{
	char	*var_value;
	char	*temp;
	int		var_len;

	(*i)++;
	var_len = len_until_delim(line + *i);
	var_value = expand_single_var(line + *i, env);
	if (!var_value)
		return (free(*result), -1);
	temp = ft_strjoin(*result, var_value);
	free(var_value);
	if (!temp)
		return (free(*result), -1);
	free(*result);
	*result = temp;
	*i += var_len;
	return (0);
}

char	*parse_dquote(char *line, char *env[])
{
	char	*result;
	int		i;
	int		start;

	i = 0;
	start = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (append_literal(&result, line, start, i) == -1)
				return (NULL);
			if (append_variable(&result, line, &i, env) == -1)
				return (NULL);
			start = i;
		}
		else
			i++;
	}
	if (append_literal(&result, line, start, i) == -1)
		return (NULL);
	return (result);
}

static int create_current_cmd(t_simple_cmd **current_cmd, t_cmd *cmds)
{
	void	*tmp;

	if (cmds->cmds_count >= cmds->cmds_capacity)
	{
		tmp = realloc(cmds->simple_cmds, sizeof(t_simple_cmd) * cmds->cmds_capacity * 2);
		if (!tmp)
			return (-1);
		cmds->simple_cmds = tmp;
		cmds->cmds_capacity *= 2;
	}
	*current_cmd = malloc(sizeof(t_simple_cmd));
	if (!*current_cmd)
		return (-1);
	(*current_cmd)->args_capacity = 4;
	(*current_cmd)->args_count = 0;
	(*current_cmd)->args = malloc(sizeof(char *) * (*current_cmd)->args_capacity);
	if (!(*current_cmd)->args)
		return (free(*current_cmd), -1);
	cmds->simple_cmds[cmds->cmds_count] = *current_cmd;
	cmds->cmds_count++;
	return (0);
}

static int	parse_word(char *word, t_simple_cmd **current_cmd, t_cmd *cmds)
{
	void	*tmp;

	if (word == NULL)
		return (-1);
	if (!*current_cmd)
	{
		if (create_current_cmd(current_cmd, cmds) == -1)
			return (-1);
	}	
	if ((*current_cmd)->args_count >= (*current_cmd)->args_capacity - 1)
	{
		tmp = realloc((*current_cmd)->args, sizeof(char *) * (*current_cmd)->args_capacity * 2);
		if (!tmp)
			return (-1);
		(*current_cmd)->args_capacity *= 2;
		(*current_cmd)->args = tmp;
	}
	(*current_cmd)->args[(*current_cmd)->args_count] = ft_strdup(word);
	if ((*current_cmd)->args[(*current_cmd)->args_count] == NULL)
		return (-1);
	(*current_cmd)->args_count++;
	(*current_cmd)->args[(*current_cmd)->args_count] = NULL;
	return (0);
}

static int handle_var_expansion(char *value, t_simple_cmd **current_cmd, t_cmd *cmds, char *env[])
{
	char	**var_expansion;
	int		i;
		
	var_expansion = expand_var(value, env);
	if (var_expansion == NULL)
		return (parse_word("", current_cmd, cmds));
	i = 0;
	while (var_expansion[i] != NULL)
	{
		if (parse_word(var_expansion[i], current_cmd, cmds) == -1)
			return (free_split(var_expansion), -1);
		i++;
	}
	free_split(var_expansion);
	return (0);
}

static int	handle_word_tokens(t_token *token, t_simple_cmd **current_cmd, t_cmd *cmds, char *env[])
{
	char	*dquote;
	int		act;

	if (token->type == WORD)
		return (parse_word(token->value, current_cmd, cmds));
	if (token->type == VAR_WORD)
		return (handle_var_expansion(token->value, current_cmd, cmds, env));
	if (token->type == DQUOTE_WORD)
	{
		dquote = parse_dquote(token->value, env);
		act = parse_word(dquote, current_cmd, cmds);
		free(dquote);
		return (act);
	}
	if (token->type == SQUOTE_WORD)
		return (parse_word(token->value, current_cmd, cmds));
	return (0);
}

static int	process_word_and_redir(t_token *token, t_simple_cmd **current_cmd, t_cmd *cmds, char *env[])
{
	if (handle_word_tokens(token, current_cmd, cmds, env) == -1)
		return (-1);
	if (token->type == PIPE)
		*current_cmd = NULL;
	return (0);
}

static int redir_in_out(t_token *tokens, int token_count, int *i, t_cmd *cmds)
{
	if (tokens[*i].type == REDIR_IN)
	{
		(*i)++;
		if (*i < token_count && tokens[*i].type == WORD)
		{
			free(cmds->in_file);
			cmds->in_file = ft_strdup(tokens[*i].value);
			if (cmds->in_file == NULL)
				return (-1);
		}
	}
	else if (tokens[*i].type == REDIR_OUT)
	{
		(*i)++;
		if (*i < token_count && tokens[*i].type == WORD)
		{
			free(cmds->out_file);
			cmds->out_file = ft_strdup(tokens[*i].value);
			if (cmds->out_file == NULL)
				return (-1);
		}
	}
	return (0);
}

static int	redir_special(t_token *tokens, int token_count, int *i, t_cmd *cmds)
{
	if (tokens[*i].type == REDIR_APPEND)
	{
		(*i)++;
		if (*i < token_count && tokens[*i].type == WORD)
		{
			free(cmds->file_append);
			cmds->file_append = ft_strdup(tokens[*i].value);
			if (cmds->file_append == NULL)
				return (-1);
		}
	}
	else if (tokens[*i].type == HERE_DOC)
	{
		(*i)++;
		if (*i < token_count && tokens[*i].type == WORD)
		{
			free(cmds->here_doc);
			cmds->here_doc = ft_strdup(tokens[*i].value);
			if (cmds->here_doc == NULL)
				return (-1);
		}
	}
	return (0);
}

static int	parse_redir(t_token *tokens, int token_count, int *i, t_cmd *cmds)
{
	if (tokens[*i].type == REDIR_IN || tokens[*i].type == REDIR_OUT)
		return (redir_in_out(tokens, token_count, i, cmds));
	else
		return (redir_special(tokens, token_count, i, cmds));
}

static int	is_redirect_token(int type)
{
	if (type == REDIR_IN)
		return (1);
	if (type == REDIR_OUT)
		return (1);
	if (type == REDIR_APPEND)
		return (1);
	if (type == HERE_DOC)
		return (1);
	return (0);
}

static int	handle_redirection(t_token *tokens, int token_count, int *i, t_cmd *cmds)
{
	if (is_redirect_token(tokens[*i].type))
		return (parse_redir(tokens, token_count, i, cmds));
	return (0);
}
//UNTIL HERE
t_cmd	*parse_tokens(t_token *tokens, int token_count, char *env[])
{
	int				i;
	t_cmd			*cmds;
	t_simple_cmd	*current_cmd;

	// int				j;
	// char			**var_expansion;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	if (cmd_init(cmds) == -1)
		return (free(cmds), NULL);
	current_cmd = NULL;
	i = 0;
	while (i < token_count && tokens[i].type != TOKEN_EOF)
	{
		//new way
		if (process_word_and_redir(&tokens[i], &current_cmd, cmds, env) == -1)
			return (free_cmd(cmds), NULL);
		if (handle_redirection(tokens, token_count, &i, cmds) == -1)
			return (free_cmd(cmds), NULL);
		i++;

		// if (tokens[i].type == WORD)
		// {
		// 	if (parse_word(tokens[i].value, &current_cmd, cmds) == -1)
		// 		return (free_cmd(cmds), NULL);
		// }
		// else if (tokens[i].type == VAR_WORD)
		// {
		// 	var_expansion = expand_var(tokens[i].value, env);
		// 	if (var_expansion == NULL)
		// 	{
		// 		if (parse_word("", &current_cmd, cmds) == -1)
		// 			return (free_cmd(cmds), NULL);
		// 	}
		// 	else
		// 	{
		// 		j = 0;
		// 		while (var_expansion[j] != NULL)
		// 		{
		// 			if (parse_word(var_expansion[j], &current_cmd, cmds) == -1)
		// 				return (free_split(var_expansion), free_cmd(cmds), NULL);
		// 			j++;
		// 		}
		// 		free_split(var_expansion);
		// 	}
		// }
		// else if (tokens[i].type == DQUOTE_WORD)
		// {
		// 	if (parse_word(parse_dquote(tokens[i].value, env), &current_cmd, cmds) == -1)
		// 		return (free_cmd(cmds), NULL);
		// }
		// else if (tokens[i].type == SQUOTE_WORD)
		// {
		// 	if (parse_word(tokens[i].value, &current_cmd, cmds) == -1)
		// 		return (free_cmd(cmds), NULL);
		// }
		// else if (tokens[i].type == REDIR_IN || tokens[i].type == REDIR_OUT
		// 	|| tokens[i].type == REDIR_APPEND || tokens[i].type == HERE_DOC)
		// {
		// 	if (parse_redir(tokens, token_count, &i, cmds) == -1)
		// 		return (free_cmd(cmds), NULL);
		// }
		// else if (tokens[i].type == PIPE)
		// 	current_cmd = NULL;
		// i++;
	}
	return (cmds);
}

