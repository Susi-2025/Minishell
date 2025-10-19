/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:21:19 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/16 16:38:03 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vector
{
	int		args_capacity;
	int		args_count;
	char	**args;
}	t_vector;

typedef struct s_simple_cmd
{
	int			args_capacity;
	int			args_count;
	char		**args;
	t_vector	*out_file;
	t_vector	*in_file;
}	t_simple_cmd;


typedef struct s_cmd
{
	int				cmds_capacity;
	int				cmds_count;
	int				err_code; //vietadd for handle error code
	t_simple_cmd	**simple_cmds; // cmd1(in, out) cmd2(in, out) cmd3(in,out)

	t_vector        *heredoc_files;
	int				heredoc_idx;

	char			*err_file;
	char			*file_append;
	char			**envp;
}	t_cmd;

typedef enum s_token_type
{
	WORD,
	DQUOTE_WORD,
	SQUOTE_WORD,
	VAR_WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HERE_DOC,
	ERROR_TOKEN,
	TOKEN_EOF,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;
#endif
// void	parse_quotes(char *l, int *i, t_token *token)
// {
// 	int		start;
// 	char	c;
// 	char	*str;
// 	char	*tmp;

// 	c = l[*i];
// 	(*i)++;
// 	start = *i;
// 	while (l[*i] && l[*i] != c)
// 		(*i)++;
// 	if (l[*i] == '\0')
// 		return (error_token(token), (void)0);
// 	str = ft_substr(l, start, *i - start);
// 	if (!str)
//         return (error_token(token), (void)0);
// 	tmp = ft_strjoin(token->value, str);
// 	free(str);
// 	free(token->value);
// 	if (tmp == NULL)
// 		return (error_token(token), (void)0);
// 	token->value = tmp;
// 	(*i)++;
// }

// void	word_token(t_token *token, char *l, int *i)
// {
// 	int		start;
// 	int		len;
// 	char	*tmp;
// 	char	*tmp2;

// 	start = *i;
// 	token->value = NULL;
// 	token->type = WORD;
// 	while (l[*i] && !is_space(l[*i]) && !is_delimiter(l[*i]))
// 	{
// 		if (l[*i] == '\"')
// 		{
// 			token->value = ft_substr(l, start, *i - start);
// 			if (token->value == NULL)
// 				return (error_token(token), (void)0);
// 			parse_quotes(l, i, token);
// 			start = *i;
// 		}
// 		(*i)++;
// 	}
// 	len = *i - start;
// 	if (len > 0)
// 	{
// 		tmp = ft_substr(l, start, len);
// 		if (tmp == NULL)
// 			return (error_token(token));
// 		tmp2 = ft_strjoin(token->value, tmp);
// 		free(tmp);
// 		if (!tmp2)
// 			return (error_token(toke));
// 		free(token->value);
// 		token->value = tmp2;
// 		if (ft_strchr(token->value, '$'))
// 			token->type = VAR_WORD;
// 		else
// 			token->type = WORD;
// 	}
// }