/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:31:18 by cwon              #+#    #+#             */
/*   Updated: 2025/07/16 09:10:42 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "builtin.h"
#include "envp.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

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

static bool	unset_arg(t_shell *shell, char *key)
{
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("unset: `", STDERR_FILENO);
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
