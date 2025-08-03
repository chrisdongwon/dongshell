/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:15:53 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 16:19:49 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "minishell.h"
#include "parser.h"

/**
 * @brief Free an AST and return NULL.
 *
 * Helper function for error handling that releases the AST
 * memory and returns a NULL pointer.
 *
 * @param ast Pointer to the AST to free.
 * @return Always returns NULL.
 */
static t_ast	*free_ast_return_null(t_ast *ast)
{
	free_ast(ast);
	return (0);
}

t_ast	*parse_subshell(t_shell *shell)
{
	t_ast		*ast;
	t_ast		*inner;
	t_parser	*parser;

	parser = shell->parser;
	if (!match(parser, TOKEN_PAREN_OPEN))
		return (0);
	inner = parse_and_or(shell);
	if (!inner || parser->syntax_error)
		return (free_ast_return_null(inner));
	if (!match(parser, TOKEN_PAREN_CLOSE))
	{
		parser->syntax_error = true;
		return (free_ast_return_null(inner));
	}
	ast = new_ast(inner, 0, AST_SUBSHELL);
	if (!ast)
		flush_and_exit(shell, "new_ast", EXIT_FAILURE);
	if (!set_command_parts(shell, parser, ast))
		return (free_ast_return_null(ast));
	return (ast);
}
