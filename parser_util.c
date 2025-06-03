/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:20:10 by cwon              #+#    #+#             */
/*   Updated: 2025/06/03 14:33:51 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_redir(t_token_type type)
{
	return (type == TOKEN_APPEND || type == TOKEN_HEREDOC || \
type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT);
}

bool	match(t_parser *parser, t_token_type type)
{
	if (peek(parser) && peek(parser)->type == type)
	{
		advance(parser);
		return (true);
	}
	return (false);
}

t_token	*advance(t_parser *parser)
{
	if (peek(parser))
		parser->token_list = parser->token_list->next;
	return (peek(parser));
}

t_token	*peek(t_parser *parser)
{
	if (!parser->token_list)
		return (0);
	return ((t_token *)parser->token_list->content);
}
