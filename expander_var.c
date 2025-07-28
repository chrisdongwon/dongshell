/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:15:09 by cwon              #+#    #+#             */
/*   Updated: 2025/07/28 14:25:41 by cwon             ###   ########.fr       */
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

static const char	*expand_exit_status(t_shell *shell, t_string *result, \
const char *pos)
{
	char	*status;

	status = ft_itoa(shell->expander->last_exit_status);
	if (!status)
		flush_and_exit(shell, "ft_itoa", EXIT_FAILURE);
	if (!append_string(result, status))
		flush_and_exit(shell, "append_string", EXIT_FAILURE);
	free(status);
	return (pos + 2);
}

static const char	*expand_variable_at(t_shell *shell, t_string *result,
const char *pos)
{
	char		*val;
	char		*var;
	const char	*next;

	var = extract_var(shell, pos + 1);
	if (shell->expander->sub_error)
	{
		free_string(result);
		return (0);
	}
	val = get_envp_value(shell->expander->envp_list, var);
	if (!val)
		val = "";
	if (!append_string(result, val))
		flush_and_exit(shell, "append_string", EXIT_FAILURE);
	next = pos + 1 + ft_strlen(var);
	free(var);
	return (next);
}

static void	append_var(t_shell *shell, t_string *result, const char **current, \
const char *dollar)
{
	char	next;

	while (*current < dollar)
	{
		if (!append_char(result, **current))
			flush_and_exit(NULL, "append_char", EXIT_FAILURE);
		(*current)++;
	}
	next = *(dollar + 1);
	if (next == '?')
		*current = expand_exit_status(shell, result, dollar);
	else if (next == '{' || ft_isalpha(next) || next == '_')
		*current = expand_variable_at(shell, result, dollar);
	else
	{
		if (!append_char(result, '$'))
			flush_and_exit(shell, "append_char", EXIT_FAILURE);
		*current = dollar + 1;
	}
}

void	expand_variable(t_shell *shell, t_token *token)
{
	const char	*current;
	const char	*dollar;
	t_string	result;

	current = token->value;
	if (!init_string(&result))
		flush_and_exit(shell, "init_string", EXIT_FAILURE);
	dollar = ft_strstr(current, "$");
	while (dollar)
	{
		append_var(shell, &result, &current, dollar);
		if (!current)
		{
			shell->expander->sub_error = true;
			return ;
		}
		dollar = ft_strstr(current, "$");
	}
	while (*current)
	{
		if (!append_char(&result, *(current++)))
			flush_and_exit(shell, "append_char", EXIT_FAILURE);
	}
	free(token->value);
	token->value = result.buffer;
}
