/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:55:32 by cwon              #+#    #+#             */
/*   Updated: 2025/05/23 09:58:40 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ast.h"

typedef struct s_parser	t_parser;

struct s_parser
{
	bool	syntax_error;
	bool	system_error;
	t_list	*token_list;
};

// parser_command.c
t_ast	*parse_command(t_parser *parser);

// parser_redir.c
t_list	*parse_redir(t_parser *parser);

// parser_subshell.c
t_ast	*parse_subshell(t_parser *parser);

// parser_util.c
bool	expect(t_parser *parser, t_token_type type);
bool	match(t_parser *parser, t_token_type type);
t_token	*current_token(t_parser *parser);
void	advance(t_parser *parser);

// parser.c
t_ast	*parse_pipeline(t_parser *parser);
t_ast	*parse(t_parser *parser);

#endif
