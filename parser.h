/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:55:32 by cwon              #+#    #+#             */
/*   Updated: 2025/07/19 22:25:11 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

# include "lexer.h"

typedef struct s_ast		t_ast;
typedef struct s_list		t_list;
typedef struct s_parser		t_parser;
typedef struct s_shell		t_shell;

struct						s_ast;
struct						s_list;
struct						s_shell;

struct s_parser
{
	bool	syntax_error;
	t_ast	*ast;
	t_list	*token_list;
};

// parser_pipeline.c
t_ast	*parse_pipeline(t_shell *shell);

// parser_redir.c
bool	is_redir(t_token_type type);
bool	validate_redir(t_shell *shell, t_ast *ast);
void	process_redir(t_shell *shell, t_ast *ast, t_token *token, \
t_token_type type);

// parse_util.c
bool	match(t_parser *parser, t_token_type type);
t_token	*advance(t_parser *parser);
t_token	*peek(t_parser *parser);
void	add_token_to_argv(t_shell *shell, t_list **argv_list, t_token *token);

// parser.c
bool	parser(t_shell *shell);
t_ast	*parse(t_shell *shell);
void	flush_parser(t_shell *shell);

#endif
