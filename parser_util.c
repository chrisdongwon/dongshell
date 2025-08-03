/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:20:10 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 09:10:07 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"
#include "minishell.h"
#include "parser.h"

bool	match(t_parser *parser, t_token_type type)
{
	if (peek(parser) && peek(parser)->type == type)
	{
		advance(parser);
		return (true);
	}
	return (false);
}

bool	parser_syntax_error(t_parser *parser)
{
	parser->syntax_error = true;
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

void	add_token_to_argv(t_shell *shell, t_list **argv_list, t_token *token)
{
	if (!append_new_token(argv_list, token->value, token->type, \
token->quote))
		flush_and_exit(shell, "append_new_token", EXIT_FAILURE);
}
