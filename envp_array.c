/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:41:12 by cwon              #+#    #+#             */
/*   Updated: 2025/07/16 15:33:15 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"

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
