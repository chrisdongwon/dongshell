/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:37:31 by cwon              #+#    #+#             */
/*   Updated: 2025/07/13 14:25:06 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "builtin.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

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
