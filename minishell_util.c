/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:04:39 by cwon              #+#    #+#             */
/*   Updated: 2025/06/02 15:26:24 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp	*new_envp_node(t_shell *shell, const char *envp_str)
{
	char	*eq;
	t_envp	*envp;

	envp = malloc(sizeof(t_envp));
	if (!envp)
		error_exit(shell, "malloc");
	envp->exported = true;
	envp->key = 0;
	envp->value = 0;
	eq = ft_strchr(envp_str, '=');
	envp->key = ft_strndup(envp_str, eq - envp_str);
	if (!envp->key)
	{
		free_envp(envp);
		error_exit(shell, "ft_strndup");
	}
	envp->value = ft_strdup(eq + 1);
	if (!envp->value)
	{
		free_envp(envp);
		error_exit(shell, "ft_strdup");
	}
	return (envp);
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
		envp_node = new_envp_node(shell, envp[i++]);
		list_node = ft_lstnew(envp_node);
		if (!list_node)
		{
			free_envp(envp_node);
			error_exit(shell, "ft_lstnew");
		}
		ft_lstadd_back(&shell->envp_list, list_node);
	}
}
