/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:41:42 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:48:08 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "builtin.h"
#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"

/**
 * @brief Create a deep copy of an environment variable structure.
 *
 * Allocates and duplicates the contents of the given t_envp structure,
 * including the key and value strings if they exist. The caller is
 * responsible for freeing the returned copy using free_envp().
 *
 * @param envp Pointer to the t_envp structure to copy.
 * @return Pointer to the copied t_envp structure, or NULL on allocation failure.
 */
static t_envp	*copy_envp(t_envp *envp)
{
	t_envp	*copy;

	if (!envp)
		return (0);
	copy = malloc(sizeof(t_envp));
	if (!copy)
		return (0);
	copy->exported = envp->exported;
	copy->key = 0;
	if (envp->key)
		copy->key = ft_strdup(envp->key);
	copy->value = 0;
	if (envp->value)
		copy->value = ft_strdup(envp->value);
	if ((envp->key && !copy->key) || (envp->value && !copy->value))
	{
		free(copy->key);
		free(copy->value);
		free(copy);
		return (0);
	}
	return (copy);
}

/**
 * @brief Create a deep copy of an environment variables linked list.
 *
 * Iterates through the provided linked list of t_envp structures, creating
 * copies of each node and adding them to a new list. If memory allocation
 * fails at any point, the partially built list is freed.
 *
 * @param head Pointer to the head of the original environment list.
 * @return Pointer to the head of the copied list, or NULL on failure.
 */
static t_list	*copy_envp_list(t_list *head)
{
	t_list	*new_head;
	t_envp	*envp_copy;
	t_list	*node_copy;

	new_head = 0;
	while (head)
	{
		envp_copy = copy_envp((t_envp *)head->content);
		if (!envp_copy)
		{
			ft_lstclear(&new_head, free_envp);
			return (0);
		}
		node_copy = ft_lstnew(envp_copy);
		if (!node_copy)
		{
			free_envp(envp_copy);
			ft_lstclear(&new_head, free_envp);
			return (0);
		}
		ft_lstadd_back(&new_head, node_copy);
		head = head->next;
	}
	return (new_head);
}

/**
 * @brief Print all exported environment variables in `declare -x` format.
 *
 * Iterates through the provided environment list and prints each exported
 * variable in the `declare -x KEY="VALUE"` format. Values are escaped
 * to properly handle special characters.
 *
 * @param shell Pointer to the shell state.
 * @param node  Pointer to the head of the environment list.
 */
static void	print_exported(t_shell *shell, t_list *node)
{
	char	*escaped;
	t_envp	*envp;

	while (node)
	{
		envp = (t_envp *)node->content;
		if (envp->exported)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(envp->key, STDOUT_FILENO);
			if (envp->value)
			{
				escaped = escape_value(envp->value);
				if (!escaped)
					flush_and_exit(shell, "escape_value", EXIT_FAILURE);
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(escaped, STDOUT_FILENO);
				ft_putchar_fd('"', STDOUT_FILENO);
				free(escaped);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		node = node->next;
	}
}

void	print_sorted_env(t_shell *shell)
{
	t_list	*temp;

	temp = copy_envp_list(shell->envp_list);
	if (!temp)
		flush_and_exit(shell, "copy_envp_list", EXIT_FAILURE);
	temp = mergesort_envp(temp);
	print_exported(shell, temp);
	ft_lstclear(&temp, free_envp);
}
