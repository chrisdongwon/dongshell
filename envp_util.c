/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 08:15:16 by cwon              #+#    #+#             */
/*   Updated: 2025/07/07 16:09:47 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_identifier(const char *key)
{
	const char	*ptr;

	if (!key || !(*key))
		return (false);
	if (!ft_isalpha(*key) && *key != '_')
		return (false);
	ptr = key + 1;
	while (*ptr)
	{
		if (!ft_isalnum(*ptr) && *ptr != '_')
			return (false);
		ptr++;
	}
	return (true);
}

char	*get_envp_value(t_list *envp_list, const char *key)
{
	t_envp	*envp;

	while (envp_list)
	{
		envp = (t_envp *)envp_list->content;
		if (!ft_strncmp(envp->key, key, ft_strlen(key) + 1))
			return (envp->value);
		envp_list = envp_list->next;
	}
	return (0);
}

t_envp	*envp_to_node(t_shell *shell, const char *envp_str)
{
	char	*eq;
	t_envp	*envp;

	envp = malloc(sizeof(t_envp));
	if (!envp)
		flush_and_exit(shell, "malloc", EXIT_FAILURE);
	envp->exported = true;
	envp->key = 0;
	envp->value = 0;
	eq = ft_strchr(envp_str, '=');
	envp->key = ft_strndup(envp_str, eq - envp_str);
	if (!envp->key)
	{
		free_envp(envp);
		flush_and_exit(shell, "ft_strndup", EXIT_FAILURE);
	}
	envp->value = ft_strdup(eq + 1);
	if (!envp->value)
	{
		free_envp(envp);
		flush_and_exit(shell, "ft_strdup", EXIT_FAILURE);
	}
	return (envp);
}

t_envp	*new_envp(t_shell *shell, const char *key, const char *value, \
bool exported)
{
	t_envp	*result;

	result = malloc(sizeof(t_envp));
	if (!result)
		flush_and_exit(shell, "malloc", EXIT_FAILURE);
	result->key = 0;
	result->value = 0;
	result->exported = exported;
	result->key = ft_strdup(key);
	if (!result->key)
	{
		free_envp(result);
		flush_and_exit(shell, "ft_strdup", EXIT_FAILURE);
	}
	result->value = ft_strdup(value);
	if (!result->value)
	{
		free_envp(result);
		flush_and_exit(shell, "ft_strdup", EXIT_FAILURE);
	}
	return (result);
}
