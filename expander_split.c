/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:56:50 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:15:32 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "expander.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

/**
 * @brief Reassign the head pointer to a new list or next node.
 *
 * If new_list is non-NULL, sets *head to new_list; otherwise sets *head to next.
 *
 * @param head     Pointer to the head pointer to reassign.
 * @param new_list New list to assign as the head, or NULL.
 * @param next     The fallback node to assign if new_list is NULL.
 */
static void	reassign_head(t_list **head, t_list *new_list, t_list *next)
{
	if (new_list)
		*head = new_list;
	else
		*head = next;
}

/**
 * @brief Append a new word token to the list.
 *
 * Duplicates the substring [start, start+len) and appends it as a TOKEN_WORD
 * token to the list. On failure, clears the list and exits.
 *
 * @param shell Pointer to the shell state.
 * @param list  Pointer to the token list to append to.
 * @param start Start of the substring to duplicate.
 * @param len   Length of the substring.
 */
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

/**
 * @brief Split a string by IFS whitespace and delimiters into tokens.
 *
 * Splits the input string according to the IFS variable's whitespace and
 * delimiter characters. Returns a list of tokens (words and delimiters).
 *
 * @param shell Pointer to the shell state.
 * @param str   The input string to split.
 * @param ifs   String containing IFS whitespace and delimiters.
 * @return      List of tokens created from the input string.
 */
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
