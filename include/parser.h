/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:20:20 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/22 14:19:52 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
/* Needed in order to use the type definitions */
# include "structs.h"

typedef struct s_expansion_state
{
	int i;
	int start;
	char *final_str;
}	t_expansion_state;

typedef struct s_expansion_context
{
	char			**env;
	int				exit_code;
	t_simple_cmd	**current_cmd;
}	t_expansion_context;

void	free_cmd(t_cmd *cmds);
int		parse_tokens(t_cmd *cmds, t_token *tokens,
			int token_count, char *env[]);
int		redir_in_out(t_token *tokens, int token_count, int *i, t_cmd *cmds);
int		redir_special(t_token *tokens, int token_count, int *i, t_cmd *cmds);
int		parse_redir(t_token *tokens, int token_count, int *i, t_cmd *cmds);
int		is_redirect_token(int type);
int		create_current_cmd(t_simple_cmd **current_cmd, t_cmd *cmds);
int		parse_word(char *word, t_simple_cmd **current_cmd);
char	*parse_dquote(char *line, int *j, char *env[], int exit_code);
int		handle_var_expansion(char *value, t_simple_cmd **current_cmd,
			char *env[]);
char	**expand_var(char *line_value, char *env[]);

char	*handle_var_exp(char *prefix, char *env_value,
			t_simple_cmd **current_cmd, char *var_name);
char	*ft_strjoin_and_free(char *s1, char *s2);

int		append_literal(char **result, char *line, int start, int end);
int		append_variable(char **result, char *line, int *i, char *env[]);

char	*parse_heredoc(char *line, char *env[], int exit_code);
int		contains_quotes(char *delimiter);
int		read_heredoc_to_file(char *del, char *filename, t_cmd *cmds);
char	*create_heredoc_file(void);
int		handle_heredoc(t_cmd *cmds, char *del);
int		syntax_checker(t_token *tokens, int t_count, t_cmd *cmds);
int	process_word(t_token *token, t_simple_cmd **current_cmd,
		char *env[], int exit_status);

int		handle_single_quote(t_expansion_state *st, char *str);
int		handle_double_quote(t_expansion_state *st, char *str,
		t_expansion_context *ctx);
int		var_expansion_helper(char *env_value, t_expansion_state *st,
	char *str, t_expansion_context *ctx);
int		handle_regular_var(t_expansion_state *st, char *str,
		t_expansion_context *ctx);
int		handle_dollar_expansion(t_expansion_state *st, char *str,
		t_expansion_context *ctx);
int		handle_redirection(t_token *tokens, int token_count, int *i,
		t_cmd *cmds);
int		is_redirect_token(int type);
#endif
