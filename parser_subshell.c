/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:22:59 by cwon              #+#    #+#             */
/*   Updated: 2025/05/23 09:58:53 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	is_valid_token(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR || \
type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT || type == TOKEN_APPEND || \
type == TOKEN_HEREDOC || type == TOKEN_PAREN_CLOSE || type == TOKEN_END);
}

static t_ast	*new_subshell_ast(t_parser *parser, t_ast *left)
{
	t_ast	*result;

	result = new_ast(left, 0, AST_SUBSHELL);
	if (!result)
	{
		parser->system_error = true;
		free_ast(left);
		return (0);
	}
	result->redir_list = parse_redir(parser);
	return (result);
}

t_ast	*parse_subshell(t_parser *parser)
{
	t_ast	*left;

	advance(parser);
	left = parse(parser);
	if (!left)
	{
		parser->syntax_error = true;
		return (0);
	}
	if (!expect(parser, TOKEN_PAREN_CLOSE))
	{
		free_ast(left);
		return (0);
	}
	if (parser->token_list && current_token(parser) && \
!is_valid_token(current_token(parser)->type))
	{
		parser->syntax_error = true;
		free_ast(left);
		return (0);
	}
	return (new_subshell_ast(parser, left));
}
