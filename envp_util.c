/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:00:26 by cwon              #+#    #+#             */
/*   Updated: 2025/05/25 21:00:51 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

static t_envp	*new_envp(const char *env_str)
{
	t_envp	*envp;

	envp = malloc(sizeof(t_envp));
	if (!envp)
		return (0);
	envp->exported = true;
	envp->key = ft_strndup(env_str, ft_strchr(env_str, '=') - env_str);
	if (!envp->key)
	{
		free(envp);
		return (0);
	}
	envp->value = ft_strdup(ft_strchr(env_str, '=') + 1);
	if (!envp->value)
	{
		free_envp(envp);
		return (0);
	}
	return (envp);
}

char	*combine_key_value(t_envp *envp)
{
	char	*result;
	size_t	len;

	len = ft_strlen(envp->key) + ft_strlen(envp->value) + 2;
	result = malloc(len);
	if (!result)
		return (0);
	result[0] = 0;
	ft_strlcat(result, envp->key, len);
	ft_strlcat(result, "=", len);
	ft_strlcat(result, envp->value, len);
	result[len - 1] = 0;
	return (result);
}

t_list	*new_envp_node(const char *env_str)
{
	t_envp	*envp;
	t_list	*result;

	envp = new_envp(env_str);
	if (!envp)
		return (0);
	result = ft_lstnew(envp);
	if (!result)
		free_envp(envp);
	return (result);
}
