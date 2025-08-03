/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:41:12 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 10:38:50 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"

/**
 * @brief Combine a key and value into a "key=value" string.
 *
 * Allocates and returns a new string consisting of the given key,
 * an '=' character, and the given value. The resulting string is
 * null-terminated.
 *
 * @param key   Null-terminated key string.
 * @param value Null-terminated value string (can be empty but not NULL).
 *
 * @return Newly allocated "key=value" string, or NULL if allocation fails.
 *
 * @note Caller is responsible for freeing the returned string.
 */
static char	*combine_key_value(const char *key, const char *value)
{
	char	*result;
	size_t	key_len;
	size_t	val_len;

	key_len = ft_strlen(key);
	val_len = ft_strlen(value);
	result = malloc(key_len + 1 + val_len + 1);
	if (!result)
		return (0);
	ft_memcpy(result, key, key_len);
	result[key_len] = '=';
	if (value)
		ft_memcpy(result + key_len + 1, value, val_len);
	result[key_len + 1 + val_len] = 0;
	return (result);
}

/**
 * @brief Count the number of exported environment variables.
 *
 * Iterates through the given linked list of environment variables
 * and counts how many have the `exported` flag set.
 *
 * @param node Pointer to the first node of the environment list.
 *
 * @return Number of exported variables.
 */
static size_t	count_exported(t_list *node)
{
	size_t	count;
	t_envp	*envp;

	count = 0;
	while (node)
	{
		envp = (t_envp *)node->content;
		if (envp->exported)
			count++;
		node = node->next;
	}
	return (count);
}

/**
 * @brief Free an array of environment variable strings and exit.
 *
 * Frees each string in the given array, then frees the array itself.
 * Calls `flush_and_exit()` with the given shell pointer.
 *
 * @param shell Pointer to the shell instance.
 * @param arr   Array of strings to free.
 * @param n     Number of strings in the array.
 *
 * @warning This function terminates the program via `flush_and_exit()`.
 */
static void	free_envp_arr(t_shell *shell, char **arr, size_t n)
{
	while (n)
		free(arr[--n]);
	free(arr);
	flush_and_exit(shell, "combine_key_value", EXIT_FAILURE);
}

char	**list_to_envp_array(t_shell *shell, t_list *node)
{
	char	**result;
	size_t	i;
	t_envp	*envp;

	result = malloc((count_exported(node) + 1) * sizeof(char *));
	if (!result)
		flush_and_exit(shell, "malloc", EXIT_FAILURE);
	i = 0;
	while (node)
	{
		envp = (t_envp *)node->content;
		if (envp->exported)
		{
			result[i] = combine_key_value(envp->key, envp->value);
			if (!result[i])
				free_envp_arr(shell, result, i);
			i++;
		}
		node = node->next;
	}
	result[i] = 0;
	return (result);
}
