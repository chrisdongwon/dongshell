/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:59:08 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:00:12 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "minishell.h"
#include "parser.h"

/**
 * @brief Initialize the parser state.
 *
 * Allocates and initializes the parser structure, linking it to
 * the token list produced by the lexer.
 *
 * @param shell Pointer to the shell instance.
 *
 * @note On allocation failure, calls flush_and_exit().
 */
static void	init_parser(t_shell *shell)
{
	shell->parser = malloc(sizeof(t_parser));
	if (!shell->parser)
		flush_and_exit(shell, "malloc", EXIT_FAILURE);
	shell->parser->syntax_error = false;
	shell->parser->ast = 0;
	shell->parser->token_list = shell->lexer->token_list;
}

bool	parser(t_shell *shell)
{
	init_parser(shell);
	shell->parser->ast = parse(shell);
	if (shell->parser->syntax_error)
	{
		shell->last_exit_status = 2;
		return (false);
	}
	return (true);
}

t_ast	*parse(t_shell *shell)
{
	t_ast		*ast;
	t_parser	*parser;

	parser = shell->parser;
	parser->syntax_error = false;
	ast = parse_and_or(shell);
	if (peek(parser) && peek(parser)->type != TOKEN_PAREN_CLOSE)
		parser->syntax_error = true;
	if (parser->syntax_error)
	{
		free_ast(ast);
		return (0);
	}
	return (ast);
}

void	flush_parser(t_shell *shell)
{
	if (!shell->parser)
		return ;
	free_ast(shell->parser->ast);
	shell->parser->ast = 0;
	free(shell->parser);
	shell->parser = 0;
}
