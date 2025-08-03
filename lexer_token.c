/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:42:39 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 10:47:20 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"

/**
 * @brief Close a quoted string during tokenization.
 *
 * Advances the input pointer past the closing quote character
 * and returns false to indicate that quoting is no longer active.
 *
 * @param s Pointer to the current position in the input string.
 * @return Always returns false, signaling that the quote is closed.
 */
static bool	close_quotes(const char **s)
{
	(*s)++;
	return (false);
}

/**
 * @brief Open a quoted string during tokenization.
 *
 * Stores the quote character and advances the input pointer past it.
 * Returns true to indicate that quoting is now active.
 *
 * @param s     Pointer to the current position in the input string.
 * @param quote Pointer to a char where the quote character will be stored.
 * @return Always returns true, signaling that quoting is active.
 */
static bool	open_quotes(const char **s, char *quote)
{
	*quote = **s;
	(*s)++;
	return (true);
}

/**
 * @brief Tokenize a sequence of characters into a word token.
 *
 * Reads characters from the input until a delimiter or operator is
 * encountered, respecting single and double quotes. Handles quoted
 * substrings, unclosed quotes, and special shell characters.
 *
 * @param lexer Pointer to the lexer instance.
 * @param input Pointer to the current position in the input string.
 *              This will be updated to the position after the token.
 * @param s     Pointer to the start position for tokenization.
 *
 * @return A newly allocated token:
 *         - TOKEN_WORD on success.
 *         - TOKEN_ERROR if an unclosed quote is detected.
 *         Returns NULL on memory allocation failure.
 *
 * @note On memory allocation failure, this function returns NULL without
 *       modifying the token list.
 */
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
