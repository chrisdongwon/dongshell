/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:37:19 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:26:55 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "ast.h"
#include "executor.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"
#include "signal_handler.h"
#include "expander.h"

/**
 * @brief Print an error message related to redirection failure.
 *
 * Prints a descriptive error message to STDERR based on the current errno
 * value for the given filename.
 *
 * @param filename The filename involved in the redirection error.
 */
static void	print_redir_error(const char *filename)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno == EACCES)
		ft_putstr_fd("Permission denied\n", STDERR_FILENO);
	else if (errno == ENOENT)
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
	else if (errno == EISDIR)
		ft_putstr_fd("Is a directory\n", STDERR_FILENO);
	else
		perror(filename);
}

/**
 * @brief Redirect standard input from a file.
 *
 * Opens the specified filename for reading and duplicates its file descriptor
 * onto STDIN_FILENO. If is_heredoc is true, the file is unlinked after opening.
 *
 * On failure, prints an error message and exits.
 *
 * @param shell      Pointer to shell context, used for error handling.
 * @param filename   The input filename to redirect from.
 * @param is_heredoc Whether this input is from a heredoc temporary file.
 */
static void	redirect_input(t_shell *shell, const char *filename, \
bool is_heredoc)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_redir_error(filename);
		flush_and_exit(shell, 0, 1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		flush_and_exit(shell, "dup2", EXIT_FAILURE);
	}
	if (is_heredoc)
		unlink(filename);
	close(fd);
}

/**
 * @brief Redirect standard output to a file.
 *
 * Opens the specified filename with given flags for writing and duplicates
 * its file descriptor onto STDOUT_FILENO.
 *
 * On failure, prints an error message and exits.
 *
 * @param shell    Pointer to shell context, used for error handling.
 * @param filename The output filename to redirect to.
 * @param flags    Flags to control opening mode (e.g., O_TRUNC or O_APPEND).
 */
static void	redirect_output(t_shell *shell, const char *filename, int flags)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | flags, 0644);
	if (fd < 0)
	{
		print_redir_error(filename);
		flush_and_exit(shell, 0, 1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		flush_and_exit(shell, "dup2", EXIT_FAILURE);
	}
	close(fd);
}

int	execute_redirection_only(t_shell *shell, t_ast *ast)
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
		exit(EXIT_SUCCESS);
	}
	return (handle_parent_signals(pid));
}

void	apply_redirections(t_shell *shell, t_list *redir_list)
{
	t_token	*token;

	while (redir_list)
	{
		token = (t_token *)redir_list->content;
		if (token->type == TOKEN_REDIR_IN)
			redirect_input(shell, token->value, false);
		else if (token->type == TOKEN_REDIR_OUT)
			redirect_output(shell, token->value, O_TRUNC);
		else if (token->type == TOKEN_APPEND)
			redirect_output(shell, token->value, O_APPEND);
		else if (token->type == TOKEN_HEREDOC)
			redirect_input(shell, token->value, true);
		redir_list = redir_list->next;
	}
}
