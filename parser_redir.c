/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:46:01 by cwon              #+#    #+#             */
/*   Updated: 2025/05/20 22:18:30 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	is_redir(t_parser *parser)
{
	return (match(parser, TOKEN_APPEND) || match(parser, TOKEN_HEREDOC) || \
match(parser, TOKEN_REDIR_IN) || match(parser, TOKEN_REDIR_OUT));
}

static bool	append_redir(t_parser *parser, t_list **redir_list, \
t_token_type redir_type)
{
	size_t	len;
	t_token	*token;

	token = current_token(parser);
	len = ft_strlen(token->value);
	token = new_token(token->value, len, redir_type, token->quote);
	if (!token)
	{
		parser->system_error = true;
		return (false);
	}
	if (!add_token(redir_list, token))
	{
		parser->system_error = true;
		free_token(token);
		return (false);
	}
	return (true);
}

t_list	*parse_redir(t_parser *parser)
{
	t_list			*result;
	t_token_type	redir_type;

	if (parser->syntax_error || parser->system_error)
		return (0);
	result = 0;
	while (is_redir(parser))
	{
		redir_type = current_token(parser)->type;
		advance(parser);
		if (!match(parser, TOKEN_WORD))
		{
			parser->syntax_error = true;
			return (0);
		}
		if (!append_redir(parser, &result, redir_type))
		{
			ft_lstclear(&result, free_token);
			return (0);
		}
		advance(parser);
	}
	return (result);
}
