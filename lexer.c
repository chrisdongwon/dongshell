/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:12:08 by cwon              #+#    #+#             */
/*   Updated: 2025/07/04 08:40:47 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_token_to_lexer(t_shell *shell, t_token **token, \
const char **ptr)
{
	while ((*token)->type != TOKEN_END && (*token)->type != TOKEN_ERROR)
	{
		if (!add_token(&shell->lexer->token_list, *token))
		{
			free_token(*token);
			flush_and_exit(shell, "add_token", EXIT_FAILURE);
		}
		free_string(shell->lexer->str);
		if (!init_string(shell->lexer->str))
			flush_and_exit(shell, "init_string", EXIT_FAILURE);
		*token = get_next_token(shell->lexer, ptr);
		if (!(*token))
			flush_and_exit(shell, "get_next_token", EXIT_FAILURE);
	}
}

static void	init_lexer(t_shell *shell)
{
	shell->lexer = malloc(sizeof(t_lexer));
	if (!shell->lexer)
		flush_and_exit(shell, "malloc", EXIT_FAILURE);
	shell->lexer->token_list = 0;
	shell->lexer->str = malloc(sizeof(t_string));
	if (!shell->lexer->str)
		flush_and_exit(shell, "malloc", EXIT_FAILURE);
	if (!init_string(shell->lexer->str))
		flush_and_exit(shell, "init_string", EXIT_FAILURE);
}

bool	lexer(t_shell *shell)
{
	bool		result;
	const char	*ptr;
	t_token		*token;

	result = true;
	init_lexer(shell);
	ptr = shell->command;
	token = get_next_token(shell->lexer, &ptr);
	if (!token)
		flush_and_exit(shell, "get_next_token", EXIT_FAILURE);
	while (token->type != TOKEN_END && token->type != TOKEN_ERROR)
		append_token_to_lexer(shell, &token, &ptr);
	if (token->type == TOKEN_ERROR)
	{
		result = false;
		shell->last_exit_status = 1;
	}
	free_token(token);
	return (result);
}

void	flush_lexer(t_shell *shell)
{
	if (!shell->lexer)
		return ;
	if (shell->lexer->token_list)
		ft_lstclear(&shell->lexer->token_list, free_token);
	if (shell->lexer->str)
		free_string(shell->lexer->str);
	free(shell->lexer->str);
	free(shell->lexer);
	shell->lexer = 0;
}
