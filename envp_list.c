/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:43:44 by cwon              #+#    #+#             */
/*   Updated: 2025/06/02 13:05:03 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_list *envp_list, const char *key)
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

void	free_envp(void *arg)
{
	t_envp	*envp;

	envp = (t_envp *)arg;
	free(envp->key);
	free(envp->value);
	free(envp);
}
