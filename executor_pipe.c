/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:50:50 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:28:26 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ast.h"
#include "executor.h"
#include "libft/libft.h"
#include "minishell.h"
#include "signal_handler.h"

/**
 * @brief Execute the left child process in a pipeline.
 *
 * Sets up input/output file descriptors for the left child in a pipeline,
 * duplicating prev_fd to STDIN and the write end of pipefd to STDOUT.
 * Closes unnecessary file descriptors and then executes the AST on the left.
 *
 * @param shell   Pointer to shell context.
 * @param ast     Pointer to the AST node representing the command.
 * @param prev_fd File descriptor for the previous pipe's read end (-1 if none).
 * @param pipefd  File descriptors of the current pipe (pipefd[0] = read end,
 *                pipefd[1] = write end).
 */
static void	exec_left_child(t_shell *shell, t_ast *ast, int prev_fd, \
int pipefd[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exit(exec_ast(shell, ast->left, true));
}

/**
 * @brief Execute the rightmost child process in a pipeline.
 *
 * Sets up input file descriptor by duplicating prev_fd to STDIN and closes
 * the previous file descriptor. Then executes the AST command.
 *
 * @param shell   Pointer to shell context.
 * @param ast     Pointer to the AST node representing the command.
 * @param prev_fd File descriptor for the previous pipe's read end (-1 if none).
 */
static void	exec_rightmost_child(t_shell *shell, t_ast *ast, int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	exit(exec_ast(shell, ast, true));
}

/**
 * @brief Wait for all child processes to terminate.
 *
 * Waits for all child processes to finish and returns the exit status
 * of the process identified by last_pid. If the process terminated by signal,
 * returns 128 + signal number.
 *
 * @param last_pid PID of the last forked process.
 * @return Exit status of the last_pid process or 0 if none.
 */
static int	wait_for_all(pid_t last_pid)
{
	int		last_status;
	int		status;
	pid_t	pid;

	last_status = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
	return (last_status);
}

/**
 * @brief Handle execution of the last process in a pipeline.
 *
 * Forks a new process to execute the rightmost command in a pipeline,
 * closes the previous file descriptor, and waits for all children.
 *
 * @param shell    Pointer to shell context.
 * @param ast      Pointer to the AST node representing the command.
 * @param prev_fd  File descriptor for the previous pipe's read end (-1 if none).
 * @param last_pid PID of the last forked child process.
 * @return Exit status of the last process or EXIT_FAILURE on error.
 */
static int	last_process(t_shell *shell, t_ast *ast, int prev_fd, \
pid_t last_pid)
{
	pid_t	pid;

	if (ast)
	{
		pid = fork_or_fail(prev_fd, 0);
		if (pid < 0)
			return (EXIT_FAILURE);
		if (!pid)
			exec_rightmost_child(shell, ast, prev_fd);
		last_pid = pid;
	}
	close_prev_fd(&prev_fd);
	return (wait_for_all(last_pid));
}

int	exec_pipe(t_shell *shell, t_ast *ast)
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	last_pid;
	pid_t	pid;

	prev_fd = -1;
	last_pid = -1;
	while (ast && ast->type == AST_PIPE)
	{
		if (create_pipe_or_fail(pipefd, prev_fd) < 0)
			return (EXIT_FAILURE);
		pid = fork_or_fail(prev_fd, pipefd);
		if (pid < 0)
			return (EXIT_FAILURE);
		if (!pid)
			exec_left_child(shell, ast, prev_fd, pipefd);
		close_prev_fd(&prev_fd);
		close(pipefd[1]);
		prev_fd = pipefd[0];
		ast = ast->right;
	}
	return (last_process(shell, ast, prev_fd, last_pid));
}
