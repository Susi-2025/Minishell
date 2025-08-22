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

int	len_until_delim(char *word)
{
	int	i;

	i = 0;
	while (word[i] && ft_isalnum(word[i]))
		i++;
	return (i);
}

int	expand_end(char **var_values, char *var_name_rest, int last_index)
{
	char	*temp;

	temp = ft_strjoin(var_values[last_index], var_name_rest);
	if (!temp)
		return (0);
	free(var_values[last_index]);
	var_values[last_index] = temp;
	return (1);
}

int	len_before_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '\0')
		return (0);
	return (i);
}

int	expand_first(char **var_values, char *line_value, int dollar_index)
{
	char	*temp;

	line_value[dollar_index] = '\0';
	temp = ft_strjoin(line_value, var_values[0]);
	if (!temp)
		return (0);
	free(var_values[0]);
	var_values[0] = temp;
	return (1);
}

char	**expand_var(char *line_value, char *env[])
{
	int		i;
	int		var_len;
	char	*env_value;
	char	**result;
	char	*variable;
	int		dollar_index;

	if (!env || !line_value)
		return (NULL);
	i = 0;
	dollar_index = len_before_dollar(line_value);
	variable = line_value + dollar_index + 1;
	var_len = len_until_delim(variable);
	while (env[i] != NULL)
	{
		if (env[i] && ft_strncmp(variable, env[i], var_len) == 0 && env[i][var_len] == '=')
		{
			env_value = ft_strdup(env[i] + var_len + 1);
			result = ft_split(env_value, ' ');
			if (dollar_index > 0)
			{
				if (!expand_first(result, line_value, dollar_index))
					return (free(env_value), free(result), NULL);
			}
			if (!result)
				return (free(env_value), NULL);
			if ((ft_strlen(variable) - var_len) > 0)
			{
				if (!expand_end(result, variable + var_len, count_strings(env_value, ' ') - 1))
					return (free(env_value), free_split(result), NULL);
			}
			return (free(env_value), result);
		}
		i++;
	}
	return (NULL);
}

static int	parse_word(char *word, t_simple_cmd **current_cmd, t_cmd *cmds)
{
	void	*tmp;

	if (!*current_cmd)
	{
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

static int	parse_redir(t_token *tokens, int token_count, int *i, t_cmd *cmds)
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
	else if (tokens[*i].type == REDIR_APPEND)
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

char    *expand_var_single(char *var, char *env[])
{
    int     i = 0;
    int     len = len_until_delim(var);
    char    *value;

    while (env[i])
    {
        if (ft_strncmp(var, env[i], len) == 0 && env[i][len] == '=')
        {
            value = ft_strdup(env[i] + len + 1);
            return (value);
        }
        i++;
    }
    return (ft_strdup(""));
}

char	*parse_dquote(char *line, char *env[])
{
	char	*result;
	char	*temp;
	char	*var_value;
	int		i;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$')
		{
			line[i] = '\0';
			temp = ft_strjoin(result, line);
			free(result);
			result = temp;
			var_value = expand_var_single(line + i + 1, env);
			temp = ft_strjoin(result, var_value);
			free(result);
			free(var_value);
			result = temp;
			i++;
			i += len_until_delim(line + i);
			line += i;
			i = 0;
			continue ;
		}
		i++;
	}
	temp = ft_strjoin(result, line);
	free(result);
	result = temp;
	return (result);
}

t_cmd	*parse_tokens(t_token *tokens, int token_count, char *env[])
{
	t_cmd			*cmds;
	int				i;
	int				j;
	t_simple_cmd	*current_cmd;
	char			**var_expansion;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	if (cmd_init(cmds) == -1)
		return (free(cmds), NULL);
	current_cmd = NULL;
	i = 0;
	while (i < token_count && tokens[i].type != TOKEN_EOF)
	{
		if (tokens[i].type == WORD)
		{
			if (parse_word(tokens[i].value, &current_cmd, cmds) == -1)
				return (free_cmd(cmds), NULL);
		}
		else if (tokens[i].type == VAR_WORD)
		{
			var_expansion = expand_var(tokens[i].value, env);
			if (var_expansion == NULL)
			{
				if (parse_word("", &current_cmd, cmds) == -1)
					return (free_cmd(cmds), NULL);
			}
			else
			{
				j = 0;
				while (var_expansion[j] != NULL)
				{
					if (parse_word(var_expansion[j], &current_cmd, cmds) == -1)
						return (free_split(var_expansion), free_cmd(cmds), NULL);
					j++;
				}
				free_split(var_expansion);
			}
		}
		else if (tokens[i].type == DQUOTE_WORD)
		{
			if (parse_word(parse_dquote(tokens[i].value, env), &current_cmd, cmds) == -1)
				return (free_cmd(cmds), NULL);

		}
		else if (tokens[i].type == REDIR_IN || tokens[i].type == REDIR_OUT
			|| tokens[i].type == REDIR_APPEND || tokens[i].type == HERE_DOC)
		{
			if (parse_redir(tokens, token_count, &i, cmds) == -1)
				return (free_cmd(cmds), NULL);
		}
		else if (tokens[i].type == PIPE)
			current_cmd = NULL;
		i++;
	}
	return (cmds);
}

