/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:51:22 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 17:16:19 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"

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

static void	prepend_env_node(t_shell *shell, t_envp *env)
{
	t_list	*new_node;

	new_node = ft_lstnew(env);
	if (!new_node)
		flush_and_exit(shell, "ft_lstnew", EXIT_FAILURE);
	ft_lstadd_front(&shell->envp_list, new_node);
}

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
