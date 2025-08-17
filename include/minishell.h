/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:25:20 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/17 16:25:22 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_simple_cmd
{
	int     args_capacity;
	int     args_count;
	char    **args;
} t_simple_cmd;

typedef struct s_cmd
{
	int cmds_capacity;
	int cmds_count;
	t_simple_cmd **simple_cmds;
	char	*out_file;
	char	*in_file;
	char	*err_file;
	char	*here_doc;
	char	*file_append;
}	t_cmd;

typedef enum {
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	TOKEN_EOF,
}	t_token_type;

typedef struct {
	t_token_type	type;
	char			*value;
}	t_token;

int     is_space(char c);
int     is_delimiter(char c);
int     ft_strlen(const char *s);
int     ft_strlcpy(char *dst, const char *src, int size);
char    *ft_strdup(const char *s);
t_token	*tokenize(char *l, int *token_count);
t_cmd	*parse_tokens(t_token *tokens, int token_count);
void	free_cmd(t_cmd *cmds);
void	free_tokens(t_token *tokens, int count);
#endif
