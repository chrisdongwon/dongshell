/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 08:53:30 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:45:50 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "builtin.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

/**
 * @brief Handle the case when `echo` is called with no arguments.
 *
 * If the argument list is empty, this function prints a newline
 * and returns `true`. Otherwise, it returns `false` so that normal
 * argument printing can continue.
 *
 * @param current Pointer to the current argument list node.
 * @return true if no arguments were given, false otherwise.
 */
static bool	echo_handle_no_args(t_list *current)
{
	if (!current)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (true);
	}
	return (false);
}

/**
 * @brief Check if a string is a valid `-n` option for `echo`.
 *
 * The `-n` option suppresses the trailing newline. This function
 * checks if the given string starts with `-` followed only by one or
 * more `n` characters and nothing else.
 *
 * @param s The string to check.
 * @return true if the string is a valid `-n` option, false otherwise.
 */
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

/**
 * @brief Parse `echo` options and advance the argument pointer.
 *
 * This function scans the argument list for consecutive `-n` options.
 * If found, it disables newline printing and moves the `current`
 * pointer past them. Parsing stops when a non-option is encountered.
 *
 * @param current Pointer to the current position in the argument list.
 * @return true if a newline should be printed, false if suppressed.
 */
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

/**
 * @brief Print the remaining `echo` arguments separated by spaces.
 *
 * Iterates over the argument list, printing each value to STDOUT and
 * separating them with a single space. No trailing space is printed.
 *
 * @param current The current position in the argument list.
 */
static void	echo_print_args(t_list *current)
{
	t_token	*token;

	while (current)
	{
		token = (t_token *)current->content;
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
