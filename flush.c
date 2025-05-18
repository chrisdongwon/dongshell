/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:56:40 by cwon              #+#    #+#             */
/*   Updated: 2025/05/18 16:24:04 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(t_shell *shell, const char *error_message)
{
	flush(shell);
	perror(error_message);
	exit(EXIT_FAILURE);
}

void	flush_lexer(t_lexer *lexer)
{
	free_string(&lexer->str);
}

void	flush(t_shell *shell)
{
	free(shell->command);
	free(shell->prompt);
	flush_lexer(&shell->lexer);
	ft_lstclear(&shell->token_list, free_token);
}
