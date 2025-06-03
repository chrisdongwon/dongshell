/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:59:08 by cwon              #+#    #+#             */
/*   Updated: 2025/06/03 15:00:21 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parser(t_shell *shell)
{
	init_parser(shell);
	shell->parser->ast = parse(shell);
	if (shell->parser->syntax_error)
	{
		shell->last_exit_status = 1;
		return (false);
	}
	return (true);
}

t_ast	*parse(t_shell *shell)
{
	t_ast		*ast;
	t_ast		*left;
	t_ast		*right;
	t_ast_type	type;
	t_parser	*parser;

	parser = shell->parser;
	if (parser->syntax_error)
		return (0);
	left = parse_pipeline(shell);
	while (peek(parser) && \
(peek(parser)->type == TOKEN_AND || peek(parser)->type == TOKEN_OR))
	{
		type = AST_AND;
		if (peek(parser)->type == TOKEN_OR)
			type = AST_OR;
		advance(parser);
		right = parse_pipeline(shell);
		ast = new_ast(left, right, type);
		if (!ast)
			error_exit(shell, "new_ast");
		left = ast;
	}
	return (left);
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

void	init_parser(t_shell *shell)
{
	shell->parser = malloc(sizeof(t_parser));
	if (!shell->parser)
		error_exit(shell, "malloc");
	shell->parser->syntax_error = false;
	shell->parser->ast = 0;
	shell->parser->token_list = shell->lexer->token_list;
}
