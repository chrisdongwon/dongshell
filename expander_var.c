/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:15:09 by cwon              #+#    #+#             */
/*   Updated: 2025/06/24 18:04:17 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_var(t_shell *shell, const char *str)
{
	char	*end;
	char	*result;
	size_t	i;

	if (str[0] == '{')
	{
		end = ft_strchr(str, '}');
		if (!end)
		{
			shell->expander->sub_error = true;
			return (0);
		}
		result = ft_strndup(str + 1, end - str - 1);
	}
	else
	{
		i = 0;
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		result = ft_strndup(str, i);
	}
	if (!result)
		error_exit(shell, "ft_strndup");
	return (result);
}

void	expand_variable(t_shell *shell, t_token *token)
{
	char	*var;
	char	*val;

	if (!ft_strncmp("$?", token->value, 3))
	{
		free(token->value);
		token->value = ft_itoa(shell->expander->last_exit_status);
		if (!token->value)
			error_exit(shell, "ft_itoa");
		return ;
	}
	var = extract_var(shell, token->value + 1);
	if (shell->expander->sub_error)
		return ;
	free(token->value);
	val = get_env_value(shell->expander->envp_list, var);
	if (!val)
		token->value = ft_strdup("");
	else
		token->value = ft_strdup(val);
	free(var);
}
