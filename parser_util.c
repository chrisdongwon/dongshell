/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:20:10 by cwon              #+#    #+#             */
/*   Updated: 2025/05/20 23:38:44 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	expect(t_parser *parser, t_token_type type)
{
	if (match(parser, type))
	{
		advance(parser);
		return (true);
	}
	parser->syntax_error = true;
	return (false);
}

bool	match(t_parser *parser, t_token_type type)
{
	return (current_token(parser) && current_token(parser)->type == type);
}

t_token	*current_token(t_parser *parser)
{
	if (!parser->token_list)
		return (0);
	return ((t_token *)parser->token_list->content);
}

void	advance(t_parser *parser)
{
	if (current_token(parser))
		parser->token_list = parser->token_list->next;
}
