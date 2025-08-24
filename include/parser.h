/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:20:20 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/24 15:20:21 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* Needed in order to use the type definitions */
#include "structs.h"
void	free_cmd(t_cmd *cmds);
t_cmd	*parse_tokens(t_token *tokens, int token_count, char *env[]);
int     redir_in_out(t_token *tokens, int token_count, int *i, t_cmd *cmds);
int	    redir_special(t_token *tokens, int token_count, int *i, t_cmd *cmds);
int	    parse_redir(t_token *tokens, int token_count, int *i, t_cmd *cmds);
int     is_redirect_token(int type);
int     create_current_cmd(t_simple_cmd **current_cmd, t_cmd *cmds);
int	    parse_word(char *word, t_simple_cmd **current_cmd, t_cmd *cmds);
char	*parse_dquote(char *line, char *env[]);
int     handle_var_expansion(char *value, t_simple_cmd **current_cmd, t_cmd *cmds, char *env[]);

#endif
