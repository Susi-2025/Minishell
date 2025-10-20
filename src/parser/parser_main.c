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

    if (!s1 && !s2)
        return (ft_strdup(""));
    if (!s1)
        return (s2); // s2 is already allocated, just return it
    if (!s2)
        return (s1); // s1 is already allocated, just return it

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
static int process_word_expansion(char *str, t_simple_cmd **current_cmd, char *env[])
{
    int     i;
    int     start;
    char    *final_cmd;
    char    *tmp;

    i = 0;
    start = 0;
    final_cmd = ft_strdup(""); // Start with an empty, allocated string
    if (!final_cmd)
		return (ERROR);
    while (str[i])
    {
        if (str[i] == '\'')
        {
            // 1. Append the unquoted part before this
            tmp = ft_substr(str, start, i - start);
            final_cmd = ft_strjoin_and_free(final_cmd, tmp);
            
            // 2. Find the closing quote and append the literal content
            i++; // Move past opening '
            start = i;
            while (str[i] && str[i] != '\'')
                i++;
            if (!str[i]) return (ERROR); // Unclosed quote error
            
            tmp = ft_substr(str, start, i - start);
            final_cmd = ft_strjoin_and_free(final_cmd, tmp);
            
            i++; // Move past closing '
            start = i;
        }
        else if (str[i] == '\"')
        {
			printf("---PROCESSING DOUBLE QUOTES-----\n");
			// 1. Append the unquoted part before this
            tmp = ft_substr(str, start, i - start);
            final_cmd = ft_strjoin_and_free(final_cmd, tmp);
            
			i++;
			tmp = parse_dquote(str + i, &i, env);
			if (tmp == NULL)
				return (ERROR);
			final_cmd = ft_strjoin_and_free(final_cmd, tmp);

            // // 2. Enter "double-quote" mode
            // i++; // Move past opening "
            // start = i;
            // while (str[i] && str[i] != '\"')
            // {
            //     if (str[i] == '$')
            //     {
            //         // Append part before $
            //         tmp = ft_substr(str, start, i - start);
            //         final_cmd = ft_strjoin_and_free(final_cmd, tmp);
                    
            //         i++; // Move past $
            //         // handle_variable expands and updates 'i'
            //         tmp = handle_variable(str, &i, env); 
            //         final_cmd = ft_strjoin_and_free(final_cmd, tmp);
            //         start = i;
            //     }
            //     else
            //         i++;
            // }
            // if (!str[i]) return (NULL); // Unclosed quote error

            // // Append final part inside quotes
            // tmp = ft_substr(str, start, i - start);
            // final_cmd = ft_strjoin_and_free(final_cmd, tmp);
            
            i++; // Move past closing "
            start = i;
        }
        else if (str[i] == '$')
        {
			printf("---PROCESSING VAR---\n");
			tmp = ft_substr(str, start, i - start);
            final_cmd = ft_strjoin_and_free(final_cmd, tmp);
			i++;
			int var_start = i;
			char *env_value = find_env_value(str + var_start, env, len_until_delim(str + var_start));
            
			i += len_until_delim(str + i);
			
			final_cmd = handle_var_exp(final_cmd, env_value, current_cmd);
            start = i;
        }
        else
        {
            i++;
        }
    }

    // Append any remaining normal characters at the end
    tmp = ft_substr(str, start, i - start);
    final_cmd = ft_strjoin_and_free(final_cmd, tmp);
	printf("final_cmd: %s\n", final_cmd);
	parse_word(final_cmd, current_cmd);
	free(final_cmd);
    return (SUCCESS);
}

// static int	process_word(char *str, t_simple_cmd **current_cmd, char *env[])
// {
// 	int	start;
// 	int	i;
// 	char	*tmp;
// 	char	*tmp2;
// 	char	*cmd;

// 	i = 0;
// 	start = 0;
// 	tmp = NULL;
// 	tmp2 = NULL;
// 	cmd = NULL;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"')
// 		{
// 			i++;
// 			tmp = parse_dquote(str + i, env);
// 			tmp2 = ft_strjoin(cmd, tmp);
// 			free(tmp);
// 			free(cmd);
// 			cmd = tmp2;
// 		}
// 		if (str[i] == '\'')
// 		{
// 			tmp = ft_substr(str,start, i - start);
// 			start = i;
// 			while (str[i] && str[i] !='\'')
// 				i++;
// 			if (!str[i])
// 				return(-1);
// 			tmp2 = ft_substr(str, start, i - start);
// 			cmd = ft_strjoin(tmp, tmp2);
// 			free(tmp);
// 			free(tmp2);
// 		}
// 		if (str[i] == '\'')
// 		{

// 		}
// 		i++;
// 	}
// 	i = 0;

// }

/*
	while (i < ft_strlen(str))
	{
	// handle for double quote
		if (dquote == 0 && squote == 0)
			temp = expand_normal(&stri])
		else if (dquote == 0 && squote == 0 && str[i] == '\"')
		{
			dquote = 1;
			expand_ignore(&str[i+1],''');
		}
		else if (dquote == 1 && str[i] == '\"')
			dquote = 0; //close dquote flag
		// handle for single quote
		else if (dquote == 0 && squote == 0 && str[i] == '\'')
		{
			squote = 1;
			temp = ft_strjoin(temp, &str[i + 1]);
		}
		else if (dquote == 0 && squote == 1 && str[i] == '\'')
			squote = 0;
		i++;
	}
*/
static int	handle_word_tokens(t_token *token, t_simple_cmd **current_cmd, char *env[])
{
	// char	*dquote;

	// int		act;

	if (token->type == WORD)
		return (process_word_expansion(token->value, current_cmd, env));
	// if (token->type == VAR_WORD)
	// 	return (handle_var_expansion(token->value, current_cmd, env));
	// if (token->type == DQUOTE_WORD)
	// {
	// 	dquote = parse_dquote(token->value, env);
	// 	act = parse_word(dquote, current_cmd);
	// 	free(dquote);
	// 	return (act);
	// }
	// if (token->type == SQUOTE_WORD)
	// 	return (parse_word(token->value, current_cmd));
	return (0);
}

static int	process_word_and_pipe(t_token *token, t_simple_cmd **current_cmd, char *env[])
{
	if (handle_word_tokens(token, current_cmd, env) == -1)
		return (-1);
	if (token->type == PIPE)
		*current_cmd = NULL;
	return (0);
}

int	handle_redir_var_expansion(t_token *token, char *env[])
{
	char	**var_expansion;
	int		i;

	var_expansion = expand_var(token->value, env);
	if (var_expansion == NULL)
		return (error_redir(token->value));
	i = 0;
	while (var_expansion[i] != NULL)
		i++;
	if (i > 1)
	{
		free_split(var_expansion);
		return (error_redir(token->value));
	}
	free(token->value);
	token->type = WORD;
	token->value = ft_strdup(var_expansion[0]);
	free_split(var_expansion);
	if (!token->value)
		return (ERROR);
	return (0);
}

static int	handle_redir_word_tokens(t_token *token, t_cmd *cmds)
{
	// char	*dquote;
	char	**env;

	env = cmds->envp;

	if (token->type == VAR_WORD)
		return (handle_redir_var_expansion(token,  env));
	// if (token->type == DQUOTE_WORD)
	// {
	// 	dquote = parse_dquote(token->value, env);
	// 	free(token->value);
	// 	token->type = WORD;
	// 	token->value = ft_strdup(dquote);
	// 	free(dquote);
	// 	if (!token->value)
	// 		return (-1);
	// }
	if (token->type == SQUOTE_WORD)
		token->type = WORD;
	return (0);
}

static int	handle_redirection(t_token *tokens, int token_count,
	int *i, t_cmd *cmds)
{
	if (is_redirect_token(tokens[*i].type))
	{
		if (tokens[*i + 1].type != TOKEN_EOF && (tokens[*i + 1].type == DQUOTE_WORD ||
			tokens[*i + 1].type == VAR_WORD || tokens[*i + 1].type == SQUOTE_WORD))
		{
			if (handle_redir_word_tokens(&tokens[*i + 1], cmds) != SUCCESS)
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
	cmds->err_code = 0; // vietadd for err_code control
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
		printf("TYPE: %d\n", tokens[i].type);
		if (process_word_and_pipe(&tokens[i], &current_cmd, env) == -1)
			return (ERROR);
		if (handle_redirection(tokens, token_count, &i, cmds) == -1)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
