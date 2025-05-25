/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:43:44 by cwon              #+#    #+#             */
/*   Updated: 2025/05/25 21:18:25 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

char	**list_to_envp_array(t_list *envp_list)
{
	char	**result;
	size_t	i;
	t_envp	*envp;

	result = ft_calloc(ft_lstsize(envp_list) + 1, sizeof(char *));
	if (!result)
		return (0);
	i = 0;
	while (envp_list)
	{
		envp = (t_envp *)envp_list->content;
		if (envp->exported)
		{
			result[i] = combine_key_value(envp);
			if (!result[i++])
			{
				free_envp_array(result);
				return (0);
			}
		}
		envp_list = envp_list->next;
	}
	return (result);
}

const char	*get_env_value(t_list *envp_list, const char *key)
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

t_list	*envp_to_list(char **envp)
{
	size_t	i;
	t_list	*result;
	t_list	*node;

	if (!envp)
		return (0);
	result = 0;
	i = 0;
	while (envp[i])
	{
		node = new_envp_node(envp[i]);
		if (!node)
		{
			ft_lstclear(&result, free_envp);
			return (0);
		}
		ft_lstadd_back(&result, node);
		i++;
	}
	return (result);
}

void	free_envp_array(char **envp)
{
	size_t	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

void	free_envp(void *arg)
{
	t_envp	*envp;

	envp = (t_envp *)arg;
	free(envp->key);
	free(envp->value);
	free(envp);
}
