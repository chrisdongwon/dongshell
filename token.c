/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 00:18:11 by cwon              #+#    #+#             */
/*   Updated: 2025/05/20 22:04:17 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	add_token(t_list **lst, t_token *token)
{
	t_list	*node;

	node = ft_lstnew(token);
	if (!node)
	{
		perror("ft_lstnew (from add_token) failed");
		return (false);
	}
	ft_lstadd_back(lst, node);
	return (true);
}

t_token	*new_token(const char *start, size_t len, t_token_type type, char quote)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		perror("malloc (from new_token) failed");
		return (0);
	}
	token->value = 0;
	if (start)
	{
		token->value = ft_strndup(start, len);
		if (!token->value)
		{
			perror("ft_strdup (from new_token) failed");
			free(token);
			return (0);
		}
	}
	token->quote = quote;
	token->type = type;
	return (token);
}

void	free_token(void *arg)
{
	t_token	*token;

	token = (t_token *)arg;
	if (token)
		free(token->value);
	free(token);
}
