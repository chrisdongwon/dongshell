/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:55:32 by cwon              #+#    #+#             */
/*   Updated: 2025/06/03 14:23:02 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ast.h"

typedef struct s_parser	t_parser;

struct s_parser
{
	bool	syntax_error;
	t_ast	*ast;
	t_list	*token_list;
};

// parse_util.c
bool	is_redir(t_token_type type);
bool	match(t_parser *parser, t_token_type type);
t_token	*advance(t_parser *parser);
t_token	*peek(t_parser *parser);

#endif
