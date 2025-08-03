/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:20:39 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 15:42:30 by cwon             ###   ########.fr       */
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
 * @brief Validate if a key is a valid export identifier.
 *
 * Checks if the given key is a valid environment variable name according
 * to shell rules: must start with an alphabetic character or underscore,
 * followed by alphanumeric characters or underscores, and optionally
 * followed by '=' and a value.
 *
 * @param key The string to validate.
 * @return true if the identifier is valid, false otherwise.
 */
static bool	is_valid_identifier_export(const char *key)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!key || !*key)
		return (false);
	while (key[i] && key[i] != '=')
		i++;
	if (!i || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (false);
	j = 1;
	while (j < i)
	{
		if (!ft_isalnum(key[j]) && key[j] != '_')
			return (false);
		j++;
	}
	return (true);
}

/**
 * @brief Export an environment variable key without a value.
 *
 * Validates the key and adds it to the environment with a NULL value
 * and the exported flag set. If invalid, prints an error message.
 *
 * @param shell Pointer to the shell state.
 * @param key   The variable name to export.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on invalid identifier.
 */
// static int	export_key_only(t_shell *shell, char *key)
// {
// 	if (!is_valid_identifier_export(key))
// 	{
// 		ft_putstr_fd("export: `", STDERR_FILENO);
// 		ft_putstr_fd(key, STDERR_FILENO);
// 		ft_putstr_fd("`: not a valid identifier\n", STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
// 	set_env(shell, key, 0, true);
// 	return (EXIT_SUCCESS);
// }

static int export_key_only(t_shell *shell, char *key)
{
	if (!is_valid_identifier_export(key))
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putstr_fd("`: not a valid identifier\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	set_env(shell, key, "", true);
	return (EXIT_SUCCESS);
}

/**
 * @brief Export an environment variable with a value.
 *
 * Splits the "key=value" string, validates the key, and adds the key/value
 * pair to the environment with the exported flag set. Prints an error if
 * the key is invalid.
 *
 * @param shell     Pointer to the shell state.
 * @param key_value String containing the key and value in "key=value" format.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on invalid identifier.
 */
static int	export_key_value(t_shell *shell, char *key_value)
{
	char	*equal;
	char	*key;
	char	*val;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	equal = ft_strchr(key_value, '=');
	key = ft_strndup(key_value, equal - key_value);
	val = ft_strdup(equal + 1);
	if (!is_valid_identifier_export(key))
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(key_value, STDERR_FILENO);
		ft_putstr_fd("`: not a valid identifier\n", STDERR_FILENO);
		exit_status = EXIT_FAILURE;
	}
	else
		set_env(shell, key, val, true);
	free(key);
	free(val);
	return (exit_status);
}

/**
 * @brief Handle an export command argument.
 *
 * Determines whether the argument is in "key=value" format or just "key"
 * and calls the appropriate export handler.
 *
 * @param shell Pointer to the shell state.
 * @param token Token containing the export argument.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE if invalid identifier.
 */
static int	handle_export_arg(t_shell *shell, t_token *token)
{
	if (ft_strchr(token->value, '='))
		return (export_key_value(shell, token->value));
	else
		return (export_key_only(shell, token->value));
}

int	builtin_export(t_shell *shell, t_list *argv_list)
{
	int		exit_status;
	int		result;
	t_token	*token;
	t_list	*node;

	exit_status = EXIT_SUCCESS;
	node = argv_list->next;
	if (!node)
	{
		print_sorted_env(shell);
		return (exit_status);
	}
	while (node)
	{
		token = (t_token *)node->content;
		if (token && token->value && *token->value)
		{
			result = handle_export_arg(shell, token);
			if (result)
				exit_status = result;
		}
		node = node->next;
	}
	return (exit_status);
}
