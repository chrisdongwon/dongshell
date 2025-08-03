/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 09:50:02 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:01:14 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "minishell.h"
#include "parser.h"

/**
 * @brief Parse an AND/OR operand.
 *
 * Parses a pipeline as a sub-expression of a logical AND/OR
 * sequence.
 *
 * @param shell Pointer to the shell instance.
 * @return Pointer to the AST node, or NULL on error.
 */
static t_ast	*parse_and_or_operand(t_shell *shell)
{
	t_ast	*node;

	node = parse_pipeline(shell);
	if (!node || shell->parser->syntax_error)
		return (0);
	return (node);
}

/**
 * @brief Convert a token type to the corresponding AST type.
 *
 * @param type Token type (TOKEN_AND or TOKEN_OR).
 * @return The corresponding AST node type.
 */
static t_ast_type	token_to_ast_type(t_token_type type)
{
	if (type == TOKEN_AND)
		return (AST_AND);
	return (AST_OR);
}

/**
 * @brief Parse the tail of an AND/OR sequence.
 *
 * Recursively parses right-hand operands of AND/OR operators,
 * constructing the corresponding AST nodes.
 *
 * @param shell Pointer to the shell instance.
 * @param left  Left-hand side AST node.
 * @return Pointer to the combined AST node, or NULL on error.
 */
static t_ast	*parse_and_or_tail(t_shell *shell, t_ast *left)
{
	t_ast			*right;
	t_parser		*parser;
	t_token_type	type;

	parser = shell->parser;
	while (peek(parser) && \
(peek(parser)->type == TOKEN_AND || peek(parser)->type == TOKEN_OR))
	{
		type = peek(parser)->type;
		advance(parser);
		right = parse_pipeline(shell);
		if (!right)
		{
			parser->syntax_error = true;
			free_ast(left);
			return (0);
		}
		left = new_ast(left, right, token_to_ast_type(type));
		if (!left)
			flush_and_exit(shell, "new_ast", EXIT_FAILURE);
	}
	return (left);
}

t_ast	*parse_and_or(t_shell *shell)
{
	t_ast	*left;

	left = parse_and_or_operand(shell);
	if (!left)
		return (0);
	return (parse_and_or_tail(shell, left));
}
