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
t_cmd	*parse_tokens(t_token *tokens, int token_count, char *env[]);
void	free_cmd(t_cmd *cmds);
void	free_tokens(t_token *tokens, int count);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *str, char c);
void	free_split(char **split);
int		ft_isalnum(int c);
int		count_strings(char const *str, char delimiter);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
#endif
