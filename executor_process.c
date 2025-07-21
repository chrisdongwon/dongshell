/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:07:38 by cwon              #+#    #+#             */
/*   Updated: 2025/07/20 00:32:50 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "ast.h"
#include "envp.h"
#include "executor.h"
#include "minishell.h"

int	create_pipe_or_fail(int pipefd[2], int prev_fd)
{
	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		if (prev_fd != -1)
			close(prev_fd);
		return (-1);
	}
	return (0);
}

pid_t	fork_or_fail(int prev_fd, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		if (prev_fd != -1)
			close(prev_fd);
		if (pipefd)
		{
			close(pipefd[0]);
			close(pipefd[1]);
		}
		return (-1);
	}
	return (pid);
}

void	close_prev_fd(int *prev_fd)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
}

void	safe_execve(t_shell *shell, t_ast *ast, char *pathname)
{
	char	**argv;
	char	**envp;

	argv = list_to_argv_array(shell, ast->argv_list);
	envp = list_to_envp_array(shell, shell->envp_list);
	execve(pathname, argv, envp);
	perror("execve");
	free(pathname);
	free_str_array(argv);
	free_str_array(envp);
	flush_and_exit(shell, 0, EXIT_FAILURE);
}
