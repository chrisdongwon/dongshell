/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:56:50 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 17:17:06 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "expander.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

static void	reassign_head(t_list **head, t_list *new_list, t_list *next)
{
	if (new_list)
		*head = new_list;
	else
		*head = next;
}

static void	add_word(t_shell *shell, t_list **list, char *start, size_t len)
{
	bool	result;
	char	*value;

	value = ft_strndup(start, len);
	if (!value)
		flush_and_exit(shell, "ft_strndup", EXIT_FAILURE);
	result = append_new_token(list, value, TOKEN_WORD, 0);
	free(value);
	if (!result)
	{
		ft_lstclear(list, free_token);
		flush_and_exit(shell, "append_new_token", EXIT_FAILURE);
	}
}

static t_list	*split_by_ifs(t_shell *shell, char *str, const char *ifs)
{
	char	*start;
	t_list	*node;

	node = 0;
	while (*str)
	{
		while (*str && ifs_whitespace(*str, ifs))
			str++;
		if (*str && ifs_delim(*str, ifs))
		{
			add_word(shell, &node, str++, 0);
			continue ;
		}
		start = str;
		while (*str && !ifs_whitespace(*str, ifs) && !ifs_delim(*str, ifs))
			str++;
		if (str > start)
			add_word(shell, &node, start, str - start);
		if (*str && ifs_delim(*str, ifs))
			str++;
	}
	return (node);
}

t_list	*replace_node(t_list **head, t_list *node, t_list *new_list)
{
	t_list	*new_tail;
	t_list	*next;
	t_list	*prev;

	if (!node)
		return (0);
	prev = node->prev;
	next = node->next;
	new_tail = new_list;
	while (new_tail && new_tail->next)
		new_tail = new_tail->next;
	new_list->prev = prev;
	new_tail->next = next;
	if (prev)
		prev->next = new_list;
	else if (head)
		reassign_head(head, new_list, next);
	if (next)
		next->prev = new_tail;
	ft_lstdelone(node, free_token);
	if (!new_tail)
		return (prev);
	return (new_tail);
}

void	expand_split(t_shell *shell, t_list **head, t_list **node)
{
	t_list	*new_list;
	t_token	*token;

	token = (t_token *)(*node)->content;
	new_list = 0;
	if (token->value)
		new_list = split_by_ifs(shell, token->value, shell->expander->ifs);
	if (!new_list)
		return ;
	if (ft_lstsize(new_list) > 1)
		*node = replace_node(head, *node, new_list);
	else
		ft_lstclear(&new_list, free_token);
}
