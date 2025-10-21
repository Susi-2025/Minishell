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


/*
** A helper you MUST write.
** Joins s1 and s2, frees both, returns new string.
** Handles NULL inputs gracefully (treats them as "").
*/
char *ft_strjoin_and_free(char *s1, char *s2)
{
    char    *new_str;

	if (!s1 || !s2)
    {
        if (s1)
            free(s1);
        if (s2)
            free(s2);
        return (NULL);
    }
    new_str = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return (new_str);
}

// /*
// ** Helper to expand a variable, e.g., $USER or $?
// ** Updates 'i' to point *after* the variable name.
// */
// char *handle_variable(char *str, int *i, char *env[])
// {
//     // 1. Find the end of the variable name (e.g., stops at space, $, ', ", etc.)
//     // 2. Get the name (e.g., "USER")
//     // 3. Look up "USER" in env[]
//     // 4. Update 'i' to point past "USER"
//     // 5. Return the value (e.g., "cdohanic") or ft_strdup("") if not found
    
//     // This is a simplified example for $?
//     if (str[*i] == '?')
//     {
//         (*i)++;
//         return (ft_itoa(g_exit_status)); // Assuming you have a global exit status
//     }
//     // ... logic for $USER, $PWD, etc. ...
    
//     // Placeholder: just skipping the var for now
//     while (ft_isalnum(str[*i]) || str[*i] == '_')
//         (*i)++;
//     return (ft_strdup("")); // Return empty string if not found
// }

/*
** This function correctly builds *one* string by processing quotes
** and variables in a single pass.
*/
static int process_word_expansion(t_token *token, t_simple_cmd **current_cmd, char *env[], int exit_code)
{
    int     i;
    int     start;
    char    *final_cmd;
    char    *tmp;
	char	*str;

    i = 0;
    start = 0;
    final_cmd = ft_strdup(""); // Start with an empty, allocated string
    if (!final_cmd)
		return (ERROR);
	str = token->value;
    while (str[i])
    {
        if (str[i] == '\'')
        {
            // 1. Append the unquoted part before this
            tmp = ft_substr(str, start, i - start);
            final_cmd = ft_strjoin_and_free(final_cmd, tmp);
			if (!final_cmd)
				return (MEM_ERROR);
			
            
            // 2. Find the closing quote and append the literal content
            i++; // Move past opening '
            start = i;
            while (str[i] && str[i] != '\'')
                i++;
            if (!str[i])
			{
				free(final_cmd);
				return (ERROR);
			}            
            tmp = ft_substr(str, start, i - start);
            final_cmd = ft_strjoin_and_free(final_cmd, tmp);
			if (!final_cmd)
				return (MEM_ERROR);
            
            i++; // Move past closing '
            start = i;
        }
        else if (str[i] == '\"')
        {
			// 1. Append the unquoted part before this
            tmp = ft_substr(str, start, i - start);
            final_cmd = ft_strjoin_and_free(final_cmd, tmp);
			if (!final_cmd)
				return (MEM_ERROR);
            
			i++;
			tmp = parse_dquote(str + i, &i, env, exit_code);
			if (tmp == NULL)
			{
				free(final_cmd);
				return (ERROR);
			}
			final_cmd = ft_strjoin_and_free(final_cmd, tmp);
			if (!final_cmd)
				return (MEM_ERROR);
            i++; // Move past closing "
            start = i;
        }
        else if (str[i] == '$')
        {
			tmp = ft_substr(str, start, i - start);
            final_cmd = ft_strjoin_and_free(final_cmd, tmp);
			if (!final_cmd)
				return (MEM_ERROR);

			i++;
			int var_start = i;
			int var_len = len_until_delim(str + var_start);
			if (str[i] != '?' && var_len == 0)
				continue ;

			char *env_value = find_env_value(str + var_start, env, len_until_delim(str + var_start));

			if (str[i] == '?')
			{
				final_cmd = ft_strjoin_and_free(final_cmd, ft_itoa(exit_code));
				if (!final_cmd)
					return (MEM_ERROR);
				i++;
			}
			else if (env_value == NULL || env_value[0] =='\0')
				free(env_value);
			else
			{
				char *var_name = ft_substr(str, var_start, len_until_delim(str + var_start));
				if (!var_name)
				{
					free(env_value);
					free(final_cmd);
					return (MEM_ERROR);
				}
				final_cmd = handle_var_exp(final_cmd, env_value, current_cmd, var_name);
				free(var_name);
				if (!final_cmd)
					return (MEM_ERROR);
			}
			i = i + var_len; 
            start = i;
        }
        else
            i++;
    }

    tmp = ft_substr(str, start, i - start);
    final_cmd = ft_strjoin_and_free(final_cmd, tmp);
	if (!final_cmd)
		return (MEM_ERROR);

	if (current_cmd != NULL && final_cmd[0] == '\0')
    {
        // If the final string is empty, we check if the *original*
        // token was an explicit quoted empty string.
        if (ft_strcmp(token->value, "\"\"") != 0 && ft_strcmp(token->value, "''") != 0)
        {
            // The original was NOT "" or ''.
            // It must have been an expansion like $non.
            // So, we discard it, just like bash.
            free(final_cmd);
            return (SUCCESS);
        }
		else
		{
			free(final_cmd);
			final_cmd = ft_strdup("''");
			if (!final_cmd)
				return (MEM_ERROR);
		}
        // If the original *was* "" or '', we fall through
        // and let it be added as a valid empty argument.
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

// static int	handle_word_tokens(t_token *token, t_simple_cmd **current_cmd, char *env[])
// {
// 	if (token->type == WORD)
// 		return (process_word_expansion(token->value, current_cmd, env));
// 	return (0);
// }

static int	process_word(t_token *token, t_simple_cmd **current_cmd, char *env[], int exit_status)
{
	// if (handle_word_tokens(token, current_cmd, env) == -1)
	// 	return (-1);
	int	return_num;
	if (token->type == WORD)
	{
		return_num = process_word_expansion(token, current_cmd, env, exit_status);
		if (return_num == MEM_ERROR)
		{
			printf("minishell: memory error\n");
			return (ERROR);
		}
		else if (return_num == ERROR)
		{
			printf("minishell: syntax error\n");
			return (ERROR);
		}
	}
	return (SUCCESS);
}

// int	handle_redir_var_expansion(t_token *token, char *env[])
// {
// 	char	**var_expansion;
// 	int		i;

// 	var_expansion = expand_var(token->value, env);
// 	if (var_expansion == NULL)
// 		return (error_redir(token->value));
// 	i = 0;
// 	while (var_expansion[i] != NULL)
// 		i++;
// 	if (i > 1)
// 	{
// 		free_split(var_expansion);
// 		return (error_redir(token->value));
// 	}
// 	free(token->value);
// 	token->type = WORD;
// 	token->value = ft_strdup(var_expansion[0]);
// 	free_split(var_expansion);
// 	if (!token->value)
// 		return (ERROR);
// 	return (0);
// }

// static int	handle_redir_word_tokens(t_token *token, t_cmd *cmds)
// {
// 	// char	*dquote;
// 	char	**env;

// 	env = cmds->envp;

// 	if (token->type == VAR_WORD)
// 		return (handle_redir_var_expansion(token,  env));
// 	// if (token->type == DQUOTE_WORD)
// 	// {
// 	// 	dquote = parse_dquote(token->value, env);
// 	// 	free(token->value);
// 	// 	token->type = WORD;ERROR
// 	// 	token->value = ft_strdup(dquote);
// 	// 	free(dquote);
// 	// 	if (!token->value)
// 	// 		return (-1);
// 	// }
// 	if (token->type == SQUOTE_WORD)
// 		token->type = WORD;
// 	return (0);
// }

static int	handle_redirection(t_token *tokens, int token_count,
	int *i, t_cmd *cmds)
{
	if (is_redirect_token(tokens[*i].type))
	{
		if (tokens[*i + 1].type != TOKEN_EOF && tokens[*i + 1].type == WORD)
		{
			if (process_word(&tokens[*i + 1], NULL, cmds->envp, cmds->err_code) != SUCCESS)
				return (ERROR);
		}
		return (parse_redir(tokens, token_count, i, cmds));
	}
	return (0);
}

int	create_current_cmd(t_simple_cmd **current_cmd, t_cmd *cmds)
{
	void	*tmp;

	if (cmds->cmds_count >= cmds->cmds_capacity)
	{
		tmp = ft_realloc(cmds->simple_cmds, sizeof(t_simple_cmd*) * cmds->cmds_capacity,
				sizeof(t_simple_cmd*) * cmds->cmds_capacity * 2);
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
	(*current_cmd)->args = malloc(sizeof(char *)
			* (*current_cmd)->args_capacity);
	if (!(*current_cmd)->args)
		return (free(*current_cmd), -1);
	(*current_cmd)->args[0] = NULL;
	(*current_cmd)->in_file = NULL;
	(*current_cmd)->out_file = NULL;
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
