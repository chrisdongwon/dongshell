/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:43:44 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 17:16:35 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"

t_envp	*get_envp(t_shell *shell, const char *key)
{
	t_envp	*env;
	t_list	*node;

	node = shell->envp_list;
	while (node)
	{
		env = (t_envp *)node->content;
		if (!ft_strcmp(env->key, key))
			return (env);
		node = node->next;
	}
	return (0);
}

void	free_envp(void *arg)
{
	t_envp	*envp;

	envp = (t_envp *)arg;
	free(envp->key);
	free(envp->value);
	free(envp);
}

void	init_envp(t_shell *shell, char **envp)
{
	size_t	i;
	t_envp	*envp_node;
	t_list	*list_node;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		envp_node = envp_to_node(shell, envp[i++]);
		list_node = ft_lstnew(envp_node);
		if (!list_node)
		{
			free_envp(envp_node);
			flush_and_exit(shell, "ft_lstnew", EXIT_FAILURE);
		}
		ft_lstadd_back(&shell->envp_list, list_node);
	}
}
