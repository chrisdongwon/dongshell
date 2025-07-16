/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:34:35 by cwon              #+#    #+#             */
/*   Updated: 2025/07/16 15:32:28 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ast.h"
#include "executor.h"
#include "minishell.h"

static int	exec_subshell(t_shell *shell, t_ast *ast)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (!pid)
		exit(exec_ast(shell, ast->left));
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	perror("fork");
	return (EXIT_FAILURE);
}

int	exec_ast(t_shell *shell, t_ast *ast)
{
	if (!ast)
		return (EXIT_SUCCESS);
	if (ast->type == AST_COMMAND)
		return (exec_command(shell, ast));
	if (ast->type == AST_PIPE)
		return (exec_pipe(shell, ast));
	if (ast->type == AST_AND)
	{
		if (!exec_ast(shell, ast->left))
			return (exec_ast(shell, ast->right));
		return (EXIT_FAILURE);
	}
	if (ast->type == AST_OR)
	{
		if (exec_ast(shell, ast->left))
			return (exec_ast(shell, ast->right));
		return (EXIT_SUCCESS);
	}
	if (ast->type == AST_SUBSHELL)
		return (exec_subshell(shell, ast));
	return (EXIT_FAILURE);
}
