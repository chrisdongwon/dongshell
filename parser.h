/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:55:32 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 10:57:53 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser.h
 * @brief Declarations for the shell command parser.
 *
 * The parser module converts a list of lexer tokens into an
 * Abstract Syntax Tree (AST) representing shell commands,
 * operators, and redirections.
 */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

# include "lexer.h"

/* Forward declarations */
typedef struct s_ast		t_ast;
typedef struct s_list		t_list;
typedef struct s_parser		t_parser;
typedef struct s_shell		t_shell;

struct						s_ast;
struct						s_list;
struct						s_shell;

/**
 * @struct s_parser
 * @brief Represents the parser state during parsing.
 *
 * Holds the current token list, the generated AST, and a syntax
 * error flag to indicate parsing errors.
 */
struct s_parser
{
	bool	syntax_error;
	t_ast	*ast;
	t_list	*token_list;
};

/* ================= parser_binary.c ================= */
/**
 * @brief Parse logical AND/OR operators into an AST.
 * @param shell Pointer to the shell instance.
 * @return Pointer to the root AST node for the AND/OR sequence.
 */
t_ast	*parse_and_or(t_shell *shell);

/* ================= parser_pipeline.c ================= */
/**
 * @brief Parse a command pipeline into an AST.
 * @param shell Pointer to the shell instance.
 * @return Pointer to the root AST node for the pipeline.
 */
t_ast	*parse_pipeline(t_shell *shell);

/* ================= parser_redir.c ================= */
/**
 * @brief Check if a token type is a redirection operator.
 * @param type Token type to check.
 * @return true if token is a redirection, false otherwise.
 */
bool	is_redir(t_token_type type);

/**
 * @brief Validate a redirection in the given AST command.
 * @param shell Pointer to the shell instance.
 * @param ast   Pointer to the AST command node.
 * @return true if the redirection is valid, false otherwise.
 */
bool	validate_redir(t_shell *shell, t_ast *ast);

/**
 * @brief Process a redirection token and attach it to the AST.
 * @param shell Pointer to the shell instance.
 * @param ast   Pointer to the AST command node.
 * @param token Redirection target token.
 * @param type  Type of the redirection token.
 */
void	process_redir(t_shell *shell, t_ast *ast, t_token *token, \
t_token_type type);

/* ================= parser_util.c ================= */
/**
 * @brief Match and consume a token of the specified type.
 * @param parser Pointer to the parser state.
 * @param type   Token type to match.
 * @return true if matched, false otherwise.
 */
bool	match(t_parser *parser, t_token_type type);

/**
 * @brief Check if the parser has encountered a syntax error.
 * @param parser Pointer to the parser state.
 * @return true if a syntax error is present, false otherwise.
 */
bool	parser_syntax_error(t_parser *parser);

/**
 * @brief Advance the parser to the next token.
 * @param parser Pointer to the parser state.
 * @return Pointer to the consumed token.
 */
t_token	*advance(t_parser *parser);

/**
 * @brief Peek at the current token without consuming it.
 * @param parser Pointer to the parser state.
 * @return Pointer to the current token.
 */
t_token	*peek(t_parser *parser);

/**
 * @brief Add a token to the AST command's argv list.
 * @param shell     Pointer to the shell instance.
 * @param argv_list Pointer to the argv list to append to.
 * @param token     Token to add.
 */
void	add_token_to_argv(t_shell *shell, t_list **argv_list, t_token *token);

/* ================= parser.c ================= */
/**
 * @brief Parse the token list into an AST.
 * @param shell Pointer to the shell instance.
 * @return true on success, false if a syntax error occurred.
 */
bool	parser(t_shell *shell);

/**
 * @brief Parse a sequence of logical AND/OR operators.
 * @param shell Pointer to the shell instance.
 * @return Pointer to the root AST node.
 */
t_ast	*parse_and_or(t_shell *shell);

/**
 * @brief Parse a command or compound command.
 * @param shell Pointer to the shell instance.
 * @return Pointer to the AST node for the parsed command.
 */
t_ast	*parse(t_shell *shell);

/**
 * @brief Free all memory used by the parser state.
 * @param shell Pointer to the shell instance.
 */
void	flush_parser(t_shell *shell);

#endif /* PARSER_H */
