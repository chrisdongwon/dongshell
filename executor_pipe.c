/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:50:50 by cwon              #+#    #+#             */
/*   Updated: 2025/07/29 12:56:14 by cwon             ###   ########.fr       */
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

static void	exec_rightmost_child(t_shell *shell, t_ast *ast, int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	exit(exec_ast(shell, ast, true));
}

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
