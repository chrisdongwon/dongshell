/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:37:31 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:43:25 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "builtin.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

/**
 * @brief Calculate the length of a string with necessary escape characters.
 *
 * This function determines how many characters the escaped version of
 * the given string will contain, including extra backslashes for escaping
 * double quotes (`"`), dollar signs (`$`), and backslashes (`\`).
 *
 * @param value The input string to measure.
 * @return size_t The length of the escaped string (excluding null terminator).
 */
static size_t	escaped_length(const char *value)
{
	const char	*ptr;
	size_t		len;

	len = 0;
	ptr = value;
	while (*ptr)
	{
		if (*ptr == '"' || *ptr == '$' || *ptr == '\\')
			len++;
		len++;
		ptr++;
	}
	return (len);
}

/**
 * @brief Copy a string into a destination buffer with escaping applied.
 *
 * This function writes an escaped version of the input string into the
 * destination buffer. It adds a backslash before any double quotes (`"`),
 * dollar signs (`$`), or backslashes (`\`).
 *
 * @param dst   Destination buffer (must be large enough to hold escaped text).
 * @param value The input string to escape.
 */
static void	fill_escaped(char *dst, const char *value)
{
	const char	*ptr;

	ptr = value;
	while (*ptr)
	{
		if (*ptr == '"' || *ptr == '$' || *ptr == '\\')
			*dst++ = '\\';
		*dst++ = *ptr++;
	}
	*dst = 0;
}

char	*escape_value(const char *value)
{
	char	*escaped;
	size_t	len;

	if (!value)
		return (ft_strdup(""));
	len = escaped_length(value);
	escaped = malloc(len + 1);
	if (!escaped)
		return (0);
	fill_escaped(escaped, value);
	return (escaped);
}

const char	*get_argv_value(t_list *argv_list, int index)
{
	int		i;
	t_list	*node;
	t_token	*token;

	node = argv_list;
	i = 0;
	while (node)
	{
		if (i++ == index)
		{
			token = (t_token *)node->content;
			return (token->value);
		}
		node = node->next;
	}
	return (0);
}

size_t	count_builtin_arguments(t_list *argv_list)
{
	size_t	count;
	t_list	*node;
	t_token	*token;

	count = 0;
	node = argv_list->next;
	while (node)
	{
		token = (t_token *)node->content;
		if (token->value)
			count++;
		node = node->next;
	}
	return (count);
}
