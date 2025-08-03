/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:31:18 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:49:33 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "builtin.h"
#include "envp.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

/**
 * @brief Check if a key is a valid identifier for the unset command.
 *
 * Determines whether the given key can be used with the unset command.
 * The key must not be NULL or empty, and it cannot begin with a dash
 * followed by another character (to avoid being mistaken for an option).
 *
 * @param key The environment variable name to check.
 * @return true if the key is valid, false otherwise.
 */
static bool	is_valid_identifier_unset(const char *key)
{
	if (!key || !*key)
		return (false);
	return (key[0] != '-' || !key[1]);
}

/**
 * @brief Remove an environment variable from the shell's environment list.
 *
 * Searches for the given key in the shell's environment variable list and
 * removes it if found. Frees all associated memory for the environment
 * variable and the list node.
 *
 * @param shell Pointer to the shell state.
 * @param key   The environment variable name to remove.
 */
static void	unset_envp(t_shell *shell, const char *key)
{
	t_envp	*envp;
	t_list	*node;

	if (!key)
		return ;
	node = shell->envp_list;
	while (node)
	{
		envp = (t_envp *)node->content;
		if (envp && envp->key && !ft_strcmp(envp->key, key))
		{
			if (node->prev)
				node->prev->next = node->next;
			else
				shell->envp_list = node->next;
			if (node->next)
				node->next->prev = node->prev;
			free_envp(envp);
			free(node);
			return ;
		}
		node = node->next;
	}
}

/**
 * @brief Handle a single unset command argument.
 *
 * Validates the given key and, if valid, removes it from the environment
 * variable list. Prints an error message for invalid keys.
 *
 * @param shell Pointer to the shell state.
 * @param key   The environment variable name to remove.
 * @return true if the variable was unset or did not exist, false if invalid.
 */
static bool	unset_arg(t_shell *shell, char *key)
{
	if (!is_valid_identifier_unset(key))
	{
		ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putstr_fd("`: not a valid identifier\n", STDERR_FILENO);
		return (false);
	}
	unset_envp(shell, key);
	return (true);
}

int	builtin_unset(t_shell *shell, t_list *argv_list)
{
	int		exit_status;
	t_list	*node;
	t_token	*token;

	exit_status = EXIT_SUCCESS;
	node = argv_list->next;
	if (!node)
		return (exit_status);
	while (node)
	{
		token = (t_token *)node->content;
		if (token && token->value && !unset_arg(shell, token->value))
			exit_status = EXIT_FAILURE;
		node = node->next;
	}
	return (exit_status);
}
