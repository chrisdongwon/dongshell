/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:05:58 by cwon              #+#    #+#             */
/*   Updated: 2025/07/07 21:04:25 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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
