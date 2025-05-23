/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:20:28 by cwon              #+#    #+#             */
/*   Updated: 2025/05/23 09:23:27 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	append_argv(t_parser *parser, t_list **argv_list)
{
	size_t	len;
	t_token	*token;

	while (current_token(parser) && current_token(parser)->type == TOKEN_WORD)
	{
		token = current_token(parser);
		len = ft_strlen(token->value);
		token = new_token(token->value, len, TOKEN_WORD, token->quote);
		if (!token)
		{
			parser->system_error = true;
			return (false);
		}
		if (!add_token(argv_list, token))
		{
			parser->system_error = true;
			free_token(token);
			return (false);
		}
		advance(parser);
	}
	return (true);
}

static bool	has_token_word(t_parser *parser)
{
	bool	result;
	t_list	*node;
	t_token	*token;

	node = parser->token_list;
	if (!node)
		return (false);
	token = (t_token *)node->content;
	result = token && token->type == TOKEN_WORD;
	if (!result)
		parser->syntax_error = true;
	return (result);
}

t_ast	*parse_command(t_parser *parser)
{
	t_ast	*result;
	t_list	*argv_list;

	if (parser->syntax_error || parser->system_error)
		return (0);
	if (match(parser, TOKEN_PAREN_OPEN))
		return (parse_subshell(parser));
	if (!has_token_word(parser))
		return (0);
	argv_list = 0;
	if (!append_argv(parser, &argv_list))
	{
		ft_lstclear(&argv_list, free_token);
		return (0);
	}
	result = new_ast(0, 0, AST_COMMAND);
	if (!result)
	{
		parser->system_error = true;
		ft_lstclear(&argv_list, free_token);
		return (0);
	}
	result->argv_list = argv_list;
	result->redir_list = parse_redir(parser);
	return (result);
}
