/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:17:46 by cwon              #+#    #+#             */
/*   Updated: 2025/07/04 08:24:37 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// exit(EXIT_FAILURE) eventually needs to be updated to indicate
// the exit signal of the failed child process...?
void	flush_and_exit(t_shell *shell, const char *error_msg, int exit_status)
{
	if (error_msg)
		perror(error_msg);
	flush_shell(shell);
	ft_lstclear(&shell->envp_list, free_envp);
	exit(exit_status);
}

void	flush_shell(t_shell *shell)
{
	free(shell->command);
	free(shell->prompt);
	flush_lexer(shell);
	flush_parser(shell);
	free(shell->expander);
	shell->expander = 0;
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
				shell.last_exit_status = exec_ast(&shell, shell.expander->ast);
			else
				ft_putstr_fd("minishell: bad substitution\n", STDERR_FILENO);
		}
		else
			ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
		flush_shell(&shell);
	}
}
