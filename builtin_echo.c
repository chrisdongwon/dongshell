/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 08:53:30 by cwon              #+#    #+#             */
/*   Updated: 2025/07/04 12:15:45 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	echo_handle_no_args(t_list *current)
{
	if (!current)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (true);
	}
	return (false);
}

static bool	is_option_n(const char *s)
{
	if (!s || *s != '-')
		return (false);
	s++;
	if (*s != 'n')
		return (false);
	while (*s == 'n')
		s++;
	return (*s == 0);
}

static bool	echo_parse_options(t_list **current)
{
	bool	newline;
	t_token	*token;

	newline = true;
	while (*current)
	{
		token = (t_token *)(*current)->content;
		if (!is_option_n(token->value))
			break ;
		newline = false;
		*current = (*current)->next;
	}
	return (newline);
}

static void	echo_print_args(t_list *current)
{
	t_token	*token;

	while (current)
	{
		token = (t_token *)current->content;
		if (token->value)
			ft_putstr_fd(token->value, STDOUT_FILENO);
		if (current->next)
			ft_putchar_fd(' ', STDOUT_FILENO);
		current = current->next;
	}
}

int	builtin_echo(t_list *argv_list)
{
	bool	newline;
	t_list	*current;

	current = argv_list->next;
	if (echo_handle_no_args(current))
		return (0);
	newline = echo_parse_options(&current);
	echo_print_args(current);
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
