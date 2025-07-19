/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:50:50 by cwon              #+#    #+#             */
/*   Updated: 2025/07/19 22:36:58 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ast.h"
#include "executor.h"
#include "minishell.h"
#include "signal_handler.h"

static pid_t	child_process(t_shell *shell, t_ast *ast, int in_fd, int out_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (!pid)
	{
		reset_signal_handlers();
		signal(SIGPIPE, SIG_DFL);
		if (in_fd >= 0)
		{
			dup2(in_fd, STDIN_FILENO);
			safe_close(in_fd);
		}
		if (out_fd >= 0)
		{
			dup2(out_fd, STDOUT_FILENO);
			safe_close(out_fd);
		}
		exit(exec_ast(shell, ast));
	}
	return (pid);
}

static int	wait_for_all(pid_t last_pid)
{
	int		result;
	int		status;
	pid_t	pid;

	result = EXIT_FAILURE;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid && WIFEXITED(status))
			result = WEXITSTATUS(status);
		pid = wait(&status);
	}
	return (result);
}

static int	last_process(t_shell *shell, t_ast *ast, int prev_fd)
{
	pid_t	last_pid;

	last_pid = child_process(shell, ast, prev_fd, -1);
	if (last_pid < 0)
	{
		safe_close(prev_fd);
		return (EXIT_FAILURE);
	}
	safe_close(prev_fd);
	return (wait_for_all(last_pid));
}

int	exec_pipe(t_shell *shell, t_ast *ast)
{
	int		pipefd[2];
	int		prev_fd;

	prev_fd = -1;
	while (ast && ast->type == AST_PIPE)
	{
		if (!safe_pipe(pipefd, prev_fd))
			return (EXIT_FAILURE);
		if (child_process(shell, ast->left, prev_fd, pipefd[1]) < 0)
		{
			safe_close(prev_fd);
			safe_close(pipefd[0]);
			safe_close(pipefd[1]);
			return (EXIT_FAILURE);
		}
		safe_close(prev_fd);
		safe_close(pipefd[1]);
		prev_fd = pipefd[0];
		ast = ast->right;
	}
	return (last_process(shell, ast, prev_fd));
}
