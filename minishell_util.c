/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:28:06 by cwon              #+#    #+#             */
/*   Updated: 2025/05/18 16:28:38 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_shell *shell)
{
	const char	*ptr;
	t_token		*token;

	if (!init_lexer(&shell->lexer))
		return (perror("init_lexer (from lexer) failed"));
	ptr = shell->command;
	token = get_next_token(&shell->lexer, &ptr);
	if (!token)
		return (perror("get_next_token (from lexer) failed"));
	while (token->type != TOKEN_END && token->type != TOKEN_ERROR)
	{
		if (!add_token(&shell->token_list, token))
			return (free_token(token));
		free_string(&shell->lexer.str);
		if (!init_string(&shell->lexer.str))
			return (perror("init_string (from lexer) failed"));
		token = get_next_token(&shell->lexer, &ptr);
		if (!token)
			return (perror("get_next_token (from lexer) failed"));
	}
	if (token->type == TOKEN_ERROR)
		shell->lexer.success = false;
	free_token(token);
}

void	read_command(t_shell *shell)
{
	shell->prompt = generate_prompt();
	if (!shell->prompt)
		error_exit(shell, "malloc (from build_prompt) failed");
	shell->command = readline(shell->prompt);
	if (!shell->command)
	{
		flush(shell);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (*(shell->command))
		add_history(shell->command);
}
