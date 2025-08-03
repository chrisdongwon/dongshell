/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:17:46 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 09:43:51 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "envp.h"
#include "executor.h"
#include "expander.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"
#include "parser.h"
#include "signal_handler.h"

/**
 * @brief Frees resources used by the shell.
 *
 * Releases allocated memory for the current command, prompt, lexer,
 * parser, and expander subsystems.
 *
 * @param shell Pointer to the shell state.
 */
static void	flush_shell(t_shell *shell)
{
	free(shell->command);
	free(shell->prompt);
	flush_lexer(shell);
	flush_parser(shell);
	flush_expander(shell);
}

/**
 * @internal
 * @brief Initializes the shell state structure.
 *
 * Sets default values for all members of the shell structure and
 * initializes environment variables and signal handlers.
 *
 * @param shell Pointer to the shell state to initialize.
 * @param envp Null-terminated array of environment variables.
 */
static void	init_shell(t_shell *shell, char **envp)
{
	shell->command = 0;
	shell->prompt = 0;
	shell->last_exit_status = 0;
	shell->envp_list = 0;
	shell->expander = 0;
	shell->lexer = 0;
	shell->parser = 0;
	init_envp(shell, envp);
	setup_signal_handlers();
}

void	flush_and_exit(t_shell *shell, const char *error_msg, int exit_status)
{
	if (error_msg)
		perror(error_msg);
	flush_shell(shell);
	ft_lstclear(&shell->envp_list, free_envp);
	exit(exit_status);
}

void	minishell(char **envp)
{
	t_shell	shell;

	init_shell(&shell, envp);
	while (true)
	{
		read_command(&shell);
		if (lexer(&shell) && parser(&shell))
		{
			if (expander(&shell))
				execute_command(&shell);
			else
				ft_putstr_fd("minishell: bad substitution\n", STDERR_FILENO);
		}
		else
			ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
		flush_shell(&shell);
	}
}
