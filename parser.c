/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:05:07 by cwon              #+#    #+#             */
/*   Updated: 2025/05/25 23:51:50 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast	*new_conditional_ast(t_parser *parser, t_ast *left, \
t_ast_type type)
{
	t_ast	*right;

	right = parse_pipeline(parser);
	if (!right)
	{
		parser->syntax_error = true;
		free_ast(left);
		return (0);
	}
	return (new_ast(left, right, type));
}

static t_ast	*new_pipeline_ast(t_parser *parser, t_ast *left)
{
	t_ast	*right;

	advance(parser);
	right = parse_command(parser);
	if (!right)
	{
		parser->syntax_error = true;
		free_ast(left);
		return (0);
	}
	return (new_ast(left, right, AST_PIPE));
}

t_ast	*parse_pipeline(t_parser *parser)
{
	t_ast	*ast;
	t_ast	*left;

	if (parser->syntax_error || parser->system_error)
		return (0);
	left = parse_command(parser);
	if (!left)
		return (0);
	while (match(parser, TOKEN_PIPE))
	{
		ast = new_pipeline_ast(parser, left);
		if (!ast)
		{
			parser->system_error = true;
			return (0);
		}
		left = ast;
	}
	return (left);
}

t_ast	*parse(t_parser *parser)
{
	t_ast		*ast;
	t_ast		*left;
	t_ast_type	type;

	if (parser->syntax_error || parser->syntax_error)
		return (0);
	left = parse_pipeline(parser);
	if (!left)
		return (0);
	while (match(parser, TOKEN_AND) || match(parser, TOKEN_OR))
	{
		type = AST_AND;
		if (current_token(parser)->type == TOKEN_OR)
			type = AST_OR;
		advance(parser);
		ast = new_conditional_ast(parser, left, type);
		if (!ast)
		{
			parser->system_error = true;
			return (0);
		}
		left = ast;
	}
	return (left);
}
