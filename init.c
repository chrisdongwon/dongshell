/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:02:38 by cwon              #+#    #+#             */
/*   Updated: 2025/05/20 18:50:23 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_lexer(t_lexer *lexer)
{
	lexer->success = true;
	if (!init_string(&lexer->str))
	{
		perror("init_string (from init_lexer) failed");
		return (false);
	}
	return (true);
}

void	init_shell(t_shell *shell)
{
	shell->command = 0;
	shell->prompt = 0;
	shell->last_exit_status = 0;
	shell->token_list = 0;
	if (!init_lexer(&shell->lexer))
		exit(EXIT_FAILURE);
}
