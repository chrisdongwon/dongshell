/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:43:44 by cwon              #+#    #+#             */
/*   Updated: 2025/08/01 15:39:42 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"

/**
 * @internal
 * @brief Appends an OLDPWD environment variable to the shell's list.
 *
 * Allocates and initializes a new environment variable node for
 * "OLDPWD" with no value, marked as exported. The new variable is
 * appended to the shell's environment list. If any allocation fails,
 * the function calls flush_and_exit() to clean up and terminate.
 *
 * @param shell Pointer to the shell state.
 *
 * @note This function is intended for internal use during shell
 *       initialization to ensure OLDPWD exists even if not inherited
 *       from the parent environment.
 */
static void	append_oldpwd_envp(t_shell *shell)
{
	t_envp	*envp_node;
	t_list	*list_node;

	envp_node = ft_calloc(1, sizeof(t_envp));
	if (!envp_node)
		flush_and_exit(shell, "ft_calloc", EXIT_FAILURE);
	envp_node->key = ft_strdup("OLDPWD");
	if (!envp_node->key)
	{
		free_envp(envp_node);
		flush_and_exit(shell, "ft_strdup", EXIT_FAILURE);
	}
	envp_node->value = 0;
	envp_node->exported = true;
	list_node = ft_lstnew(envp_node);
	if (!list_node)
	{
		free_envp(envp_node);
		flush_and_exit(shell, "ft_lstnew", EXIT_FAILURE);
	}
	ft_lstadd_back(&shell->envp_list, list_node);
}

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
	bool	oldpwd_found;
	size_t	i;
	t_envp	*envp_node;
	t_list	*list_node;

	oldpwd_found = false;
	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		envp_node = envp_to_node(shell, envp[i++]);
		if (envp_node->key && !ft_strcmp(envp_node->key, "OLDPWD"))
			oldpwd_found = true;
		list_node = ft_lstnew(envp_node);
		if (!list_node)
		{
			free_envp(envp_node);
			flush_and_exit(shell, "ft_lstnew", EXIT_FAILURE);
		}
		ft_lstadd_back(&shell->envp_list, list_node);
	}
	if (!oldpwd_found)
		append_oldpwd_envp(shell);
}
