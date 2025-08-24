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

#include "structs.h"

t_cmd	*parse_tokens(t_token *tokens, int token_count, char *env[]);
void	free_cmd(t_cmd *cmds);
#endif
