/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:32:44 by cwon              #+#    #+#             */
/*   Updated: 2025/05/25 23:48:26 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flush_lexer(t_lexer *lexer)
{
	free_string(&lexer->str);
}

void	flush_shell(t_shell *shell)
{
	free(shell->command);
	free(shell->prompt);
	flush_lexer(&shell->lexer);
	ft_lstclear(&shell->token_list, free_token);
	free_ast(shell->ast);
	shell->ast = 0;
}
