/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:10:58 by cwon              #+#    #+#             */
/*   Updated: 2025/07/08 12:25:00 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*merge(t_list *left, t_list *right)
{
	t_envp	*envp_left;
	t_envp	*envp_right;

	if (!left)
		return (right);
	if (!right)
		return (left);
	envp_left = (t_envp *)left->content;
	envp_right = (t_envp *)right->content;
	if (ft_strcmp(envp_left->key, envp_right->key) <= 0)
	{
		left->next = merge(left->next, right);
		if (left->next)
			left->next->prev = left;
		left->prev = 0;
		return (left);
	}
	else
	{
		right->next = merge(left, right->next);
		if (right->next)
			right->next->prev = right;
		right->prev = 0;
		return (right);
	}
}

static void	split(t_list *node, t_list **front, t_list **back)
{
	t_list	*fast;
	t_list	*slow;

	slow = node;
	fast = node->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = node;
	*back = slow->next;
	slow->next = 0;
	if (*back)
		(*back)->prev = 0;
}

t_list	*mergesort_envp(t_list *node)
{
	t_list	*left;
	t_list	*right;

	if (!node || !node->next)
		return (node);
	left = 0;
	right = 0;
	split(node, &left, &right);
	left = mergesort_envp(left);
	right = mergesort_envp(right);
	return (merge(left, right));
}
