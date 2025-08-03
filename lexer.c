/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:12:08 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 10:58:12 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

/**
 * @brief Append tokens from the lexer to the shell's token list.
 *
 * Iteratively adds tokens from the lexer into the shell's token list
 * until a TOKEN_END or TOKEN_ERROR is encountered. After adding each
 * token, the lexer string buffer is reset and a new token is fetched.
 *
 * @param shell Pointer to the shell instance containing the lexer state.
 * @param token Pointer to the current token pointer. This will be updated
 *              to the next token after each append.
 * @param ptr   Pointer to the current input position in the source string.
 *
 * @note If any allocation or token retrieval fails, this function will
 *       call flush_and_exit(), terminating the program.
 */
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

/**
 * @brief Initialize the lexer for the shell.
 *
 * Allocates memory for the lexer structure and its dynamic string buffer.
 * Also initializes the token list to NULL and the string buffer to an
 * empty state.
 *
 * @param shell Pointer to the shell instance whose lexer will be set up.
 *
 * @note On allocation or initialization failure, this function calls
 *       flush_and_exit(), which terminates the program.
 */
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
