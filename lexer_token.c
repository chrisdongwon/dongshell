/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:42:39 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 16:16:06 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"

static bool	close_quotes(const char **s)
{
	(*s)++;
	return (false);
}

static bool	open_quotes(const char **s, char *quote)
{
	*quote = **s;
	(*s)++;
	return (true);
}

// do i need to take care of nested quotes?
// what to do if nested quotes are unmatched? does it matter?
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
		else if (!append_char(lexer->str, *s++))
			return (0);
	}
	*input = s;
	if (open_quote)
		return (new_token("Unclosed quote", 14, TOKEN_ERROR, 0));
	return (new_token(lexer->str->buffer, lexer->str->size, TOKEN_WORD, quote));
}

t_token	*get_next_token(t_lexer *lexer, const char **input)
{
	const char	*s;

	s = *input;
	while (ft_isspace(*s))
		s++;
	if (!*s)
	{
		*input = s;
		return (new_token("", 0, TOKEN_END, 0));
	}
	if (*s == ';' || *s == '\\')
	{
		(*input) = s + 1;
		return (new_token(s, 1, TOKEN_ERROR, 0));
	}
	if (ft_strchr("<>|&()", *s))
		return (handle_operator(input, s));
	return (tokenize(lexer, input, s));
}
