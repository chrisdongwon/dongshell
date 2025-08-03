/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:37:33 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:30:57 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "builtin.h"
#include "executor.h"
#include "lexer.h"
#include "libft/libft.h"
#include "signal_handler.h"

/**
 * @brief Execute a builtin command.
 *
 * Compares the command string with known builtins and calls the corresponding
 * builtin function. Returns the builtin's return code, or EXIT_FAILURE if the
 * command is not a builtin.
 *
 * @param shell     Pointer to the shell state.
 * @param argv_list List of command arguments (tokens).
 * @return Exit status code from the builtin command or EXIT_FAILURE if unknown.
 */
static int	exec_builtin(t_shell *shell, t_list *argv_list)
{
	char	*cmd;
	t_token	*token;

	token = (t_token *)argv_list->content;
	cmd = token->value;
	if (!ft_strcmp(cmd, "cd"))
		return (builtin_cd(shell, argv_list));
	if (!ft_strcmp(cmd, "echo"))
		return (builtin_echo(argv_list));
	if (!ft_strcmp(cmd, "env"))
		return (builtin_env(shell));
	if (!ft_strcmp(cmd, "exit"))
		return (builtin_exit(shell, argv_list));
	if (!ft_strcmp(cmd, "export"))
		return (builtin_export(shell, argv_list));
	if (!ft_strcmp(cmd, "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd, "unset"))
		return (builtin_unset(shell, argv_list));
	return (EXIT_FAILURE);
}

/**
 * @brief Handle execution of a builtin command in a pipeline child process.
 *
 * Forks a new process to run the builtin. In the child process, resets signal
 * handlers, applies redirections, and executes the builtin. The parent process
 * handles the child signals.
 *
 * @param shell Pointer to the shell state.
 * @param ast   AST node containing the builtin command.
 * @return Exit status from the child process or EXIT_FAILURE if fork fails.
 */
static int	handle_pipeline(t_shell *shell, t_ast *ast)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (!pid)
	{
		reset_signal_handlers();
		apply_redirections(shell, ast->redir_list);
		exit(exec_builtin(shell, ast->argv_list));
	}
	return (handle_parent_signals(pid));
}

bool	is_builtin(t_list *argv_list)
{
	char	*cmd;
	t_token	*token;

	if (!argv_list)
		return (false);
	token = (t_token *)argv_list->content;
	cmd = token->value;
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || \
!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit") || \
!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "pwd") || \
!ft_strcmp(cmd, "unset"));
}

int	exec_builtin_with_redirection(t_shell *shell, t_ast *ast, bool in_pipeline)
{
	int	status;
	int	stdin_dup;
	int	stdout_dup;

	if (in_pipeline)
		return (handle_pipeline(shell, ast));
	stdin_dup = dup(STDIN_FILENO);
	stdout_dup = dup(STDOUT_FILENO);
	if (stdin_dup < 0 || stdout_dup < 0)
	{
		perror("dup");
		return (EXIT_FAILURE);
	}
	apply_redirections(shell, ast->redir_list);
	status = exec_builtin(shell, ast->argv_list);
	if (dup2(stdin_dup, STDIN_FILENO) < 0 || \
dup2(stdout_dup, STDOUT_FILENO) < 0)
		perror("dup2");
	close(stdin_dup);
	close(stdout_dup);
	return (status);
}
