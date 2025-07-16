/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:47:24 by cwon              #+#    #+#             */
/*   Updated: 2025/07/13 14:25:19 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "builtin.h"
#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"

int	builtin_env(t_shell *shell)
{
	t_list	*current;
	t_envp	*env_node;

	current = shell->envp_list;
	while (current)
	{
		env_node = (t_envp *)current->content;
		if (env_node->exported && env_node->value)
		{
			ft_putstr_fd(env_node->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(env_node->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		current = current->next;
	}
	return (0);
}
