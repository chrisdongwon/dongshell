/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:21:06 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:47:28 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "builtin.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

/**
 * @brief Handle non-numeric argument error for the `exit` builtin.
 *
 * Prints an error message to standard error indicating that the provided
 * argument is not numeric, then terminates the shell with exit status 2.
 *
 * @param shell Pointer to the shell state.
 * @param token Pointer to the token containing the invalid argument.
 */
static void	non_numeric_arg(t_shell *shell, t_token *token)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(token->value, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	flush_and_exit(shell, 0, 2);
}

int	builtin_exit(t_shell *shell, t_list *argv_list)
{
	t_list	*argv_1;
	t_list	*argv_2;
	t_token	*token;

	argv_1 = argv_list->next;
	argv_2 = 0;
	if (argv_1)
		argv_2 = argv_1->next;
	if (!argv_1)
		flush_and_exit(shell, 0, shell->last_exit_status);
	token = (t_token *)argv_1->content;
	if (!is_numeric_long(token->value))
		non_numeric_arg(shell, token);
	if (argv_2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	flush_and_exit(shell, 0, (unsigned char)str_to_long(token->value));
	return (EXIT_FAILURE);
}
