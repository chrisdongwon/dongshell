/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:07:38 by cwon              #+#    #+#             */
/*   Updated: 2025/07/15 12:12:40 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "ast.h"
#include "envp.h"
#include "executor.h"
#include "minishell.h"

bool	safe_pipe(int pipefd[2], int prev_fd)
{
	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		safe_close(prev_fd);
		return (false);
	}
	return (true);
}

void	safe_close(int fd)
{
	if (fd >= 0)
		close(fd);
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
