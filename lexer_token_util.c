/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:30:23 by cwon              #+#    #+#             */
/*   Updated: 2025/07/22 20:36:20 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "lexer.h"
#include "libft/libft.h"

bool	add_token(t_list **list, t_token *token)
{
	t_list	*node;

	node = ft_lstnew(token);
	if (!node)
		return (false);
	ft_lstadd_back(list, node);
	return (true);
}

bool	append_new_token(t_list **list, const char *value, t_token_type type, \
const char quote)
{
	t_token	*token;

	token = new_token(value, ft_strlen(value), type, quote);
	return (token && add_token(list, token));
}

t_token	*new_token(const char *start, size_t len, t_token_type type, char quote)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->value = 0;
	if (start)
	{
		token->value = ft_strndup(start, len);
		if (!token->value)
		{
			free(token);
			return (0);
		}
	}
	token->quote = quote;
	token->type = type;
	return (token);
}

t_token_type	get_token_type(const char *op)
{
	if (!ft_strncmp(op, "&&", 3))
		return (TOKEN_AND);
	if (!ft_strncmp(op, ">>", 3))
		return (TOKEN_APPEND);
	if (!ft_strncmp(op, "<<", 3))
		return (TOKEN_HEREDOC);
	if (!ft_strncmp(op, "||", 3))
		return (TOKEN_OR);
	if (!ft_strncmp(op, ")", 1))
		return (TOKEN_PAREN_CLOSE);
	if (!ft_strncmp(op, "(", 1))
		return (TOKEN_PAREN_OPEN);
	if (!ft_strncmp(op, "|", 2))
		return (TOKEN_PIPE);
	if (!ft_strncmp(op, "<", 2))
		return (TOKEN_REDIR_IN);
	if (!ft_strncmp(op, ">", 2))
		return (TOKEN_REDIR_OUT);
	return (TOKEN_ERROR);
}

void	free_token(void *arg)
{
	t_token	*token;

	token = (t_token *)arg;
	if (token)
		free(token->value);
	free(token);
}
