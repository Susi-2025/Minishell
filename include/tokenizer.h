/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:20:12 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/24 15:20:14 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/* Needed in order to use t_token type*/
# include "structs.h"

/* Main tokenizer functions*/
t_token	*tokenize(char *l, int *token_count);
void	free_tokens(t_token *tokens, int count);

/* Token creation functions*/
void	redir_token(t_token *token, int *i, char *l);
void	handle_redir_out(t_token *token, int *i, char *l);
void	handle_redir_in(t_token *token, int *i, char *l);
void	quote_word_token(t_token *token, int *i, char *l);
void	word_token(t_token *token, char *l, int *i);
void	eof_token(t_token *tokens, int *count);
void	pipe_token(t_token *token, int *i);
void	error_token(t_token *token);

/* String utility */
int		skip_whitespace(char *l, int i);
#endif
