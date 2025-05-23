/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:35:32 by cwon              #+#    #+#             */
/*   Updated: 2025/05/22 15:03:36 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*handle_end(const char **input, const char *s)
{
	*input = s;
	return (new_token("", 0, TOKEN_END, 0));
}

static t_token	*handle_end_op(const char **input, const char *s)
{
	(*input) = s + 1;
	return (new_token(s, 1, TOKEN_ERROR, 0));
}

static t_token	*handle_op(const char **input, const char *s)
{
	char		buffer[3];
	size_t		len;

	ft_bzero(buffer, 3);
	len = match_operator(s, buffer);
	if (!len)
		return (new_token("Unknown operator", 16, TOKEN_ERROR, 0));
	*input = s + len;
	return (new_token(buffer, len, get_token_type(buffer), 0));
}

static t_token	*tokenize(t_lexer *lexer, const char **input, const char *s)
{
	bool	open_quote;
	char	quote;

	quote = 0;
	open_quote = false;
	while (*s)
	{
		if (!open_quote && \
(ft_isspace(*s) || ft_strchr("<>|&()", *s) || *s == ';' || *s == '\\'))
			break ;
		if (!open_quote && (*s == '\'' || *s == '"'))
			open_quote = open_quotes(&s, &quote);
		else if (open_quote && *s == quote)
			open_quote = close_quotes(&s);
		else if (!append_char(&lexer->str, *s++))
			return (0);
	}
	*input = s;
	if (open_quote)
		return (new_token("Unclosed quote", 14, TOKEN_ERROR, 0));
	return (new_token(lexer->str.buffer, lexer->str.size, TOKEN_WORD, quote));
}

t_token	*get_next_token(t_lexer *lexer, const char **input)
{
	const char	*s;

	s = *input;
	while (ft_isspace(*s))
		s++;
	if (!*s)
		return (handle_end(input, s));
	if (*s == ';' || *s == '\\')
		return (handle_end_op(input, s));
	if (ft_strchr("<>|&()", *s))
		return (handle_op(input, s));
	return (tokenize(lexer, input, s));
}
