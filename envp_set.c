/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:51:22 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 10:38:06 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"

/**
 * @brief Retrieve a node from the environment variable list by key.
 *
 * Searches the shell's environment variable list (`shell->envp_list`)
 * for a variable whose `key` matches the given `key` parameter.
 *
 * @param shell Pointer to the shell structure containing the environment list.
 * @param key   Null-terminated string representing the environment variable 
 *              name.
 *
 * @return Pointer to the matching list node if found, or `NULL` if not found.
 *
 * @note The returned node's `content` is a pointer to a `t_envp` structure.
 */
static t_list	*get_envp_node(t_shell *shell, const char *key)
{
	t_envp	*envp;
	t_list	*node;

	node = shell->envp_list;
	while (node)
	{
		envp = (t_envp *)node->content;
		if (envp && envp->key && !ft_strcmp(envp->key, key))
			return (node);
		node = node->next;
	}
	return (0);
}

/**
 * @brief Prepend an environment variable node to the environment list.
 *
 * Creates a new list node containing the given `t_envp` structure and
 * inserts it at the front of the shell's environment variable list.
 *
 * @param shell Pointer to the shell structure containing the environment list.
 * @param env   Pointer to the `t_envp` structure representing the environment 
 *              variable.
 *
 * @warning If memory allocation for the new node fails, this function
 *          calls `flush_and_exit()` and terminates the program.
 */
static void	prepend_env_node(t_shell *shell, t_envp *env)
{
	t_list	*new_node;

	new_node = ft_lstnew(env);
	if (!new_node)
		flush_and_exit(shell, "ft_lstnew", EXIT_FAILURE);
	ft_lstadd_front(&shell->envp_list, new_node);
}

/**
 * @brief Update an environment variable's value and export status.
 *
 * Frees any existing value in the `t_envp` structure and replaces it
 * with a newly duplicated string from `value` if provided. Also sets
 * the exported flag if `exported` is `true`.
 *
 * @param env      Pointer to the environment variable structure to update.
 * @param value    New value string to assign (can be `NULL` to unset the 
 *                 value).
 * @param exported Boolean flag indicating whether the variable should be 
 *                 exported.
 *
 * @note If `value` is non-NULL, it is duplicated with `ft_strdup()`; the caller
 *       retains ownership of the original `value` pointer.
 */
static void	update_env(t_envp *env, const char *value, bool exported)
{
	if (env->value)
	{
		free(env->value);
		env->value = 0;
	}
	if (value)
		env->value = ft_strdup(value);
	if (exported)
		env->exported = true;
}

void	set_env(t_shell *shell, const char *key, const char *value, \
bool exported)
{
	t_list	*node;

	if (!key)
		return ;
	node = get_envp_node(shell, key);
	if (node)
		update_env((t_envp *)node->content, value, exported);
	else
		prepend_env_node(shell, new_envp(shell, key, value, exported));
}
