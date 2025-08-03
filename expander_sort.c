/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:05:58 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:16:29 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lexer.h"
#include "libft/libft.h"

/**
 * @brief Split a linked list into two halves.
 *
 * Uses the fast/slow pointer strategy to split the given linked list into two
 * roughly equal halves. The front half is assigned to *front, and the back half
 * to *back. The original list is modified by terminating the front half.
 *
 * @param list  The original linked list to split.
 * @param front Pointer to store the front half of the list.
 * @param back  Pointer to store the back half of the list.
 */
static void	split_list(t_list *list, t_list **front, t_list **back)
{
	t_list	*slow;
	t_list	*fast;

	slow = list;
	fast = list->next;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	*front = list;
	*back = slow->next;
	slow->next = 0;
	if (*back)
		(*back)->prev = 0;
}

/**
 * @brief Compare the string values of two tokens.
 *
 * Compares the 'value' fields of the tokens contained in two linked list nodes
 * using string comparison. Used for sorting or ordering tokens.
 *
 * @param a First list node containing a token.
 * @param b Second list node containing a token.
 * @return  Negative, zero, or positive integer depending on lexical order.
 */
static int	compare_token_values(t_list *a, t_list *b)
{
	t_token	*token_a;
	t_token	*token_b;

	token_a = (t_token *)a->content;
	token_b = (t_token *)b->content;
	return (ft_strcmp(token_a->value, token_b->value));
}

t_list	*merge_token_nodes(t_list *a, t_list *b)
{
	a->next = merge_token(a->next, b);
	if (a->next)
		a->next->prev = a;
	a->prev = 0;
	return (a);
}

t_list	*merge_token(t_list *front, t_list *back)
{
	if (!front)
		return (back);
	if (!back)
		return (front);
	if (compare_token_values(front, back) <= 0)
		return (merge_token_nodes(front, back));
	else
		return (merge_token_nodes(back, front));
}

t_list	*mergesort_token(t_list *list)
{
	t_list	*front;
	t_list	*back;

	if (!list || !list->next)
		return (list);
	split_list(list, &front, &back);
	front = mergesort_token(front);
	back = mergesort_token(back);
	return (merge_token(front, back));
}
