/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:15:09 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 17:17:17 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "envp.h"
#include "expander.h"
#include "lexer.h"
#include "libft/libft.h"
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
		flush_and_exit(shell, "ft_strndup", EXIT_FAILURE);
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
			flush_and_exit(shell, "ft_itoa", EXIT_FAILURE);
		return ;
	}
	var = extract_var(shell, token->value + 1);
	if (shell->expander->sub_error)
		return ;
	free(token->value);
	val = get_envp_value(shell->expander->envp_list, var);
	if (!val)
		token->value = ft_strdup("");
	else
		token->value = ft_strdup(val);
	free(var);
}
