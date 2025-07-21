/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:34:35 by cwon              #+#    #+#             */
/*   Updated: 2025/07/20 00:27:15 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ast.h"
#include "executor.h"
#include "minishell.h"

static int	exec_subshell(t_shell *shell, t_ast *ast, bool in_pipeline)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (!pid)
		exit(exec_ast(shell, ast->left, in_pipeline));
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (EXIT_FAILURE);
	}
}

int	exec_ast(t_shell *shell, t_ast *ast, bool in_pipeline)
{
	if (!ast)
		return (EXIT_SUCCESS);
	if (ast->type == AST_COMMAND)
		return (exec_command(shell, ast, in_pipeline));
	if (ast->type == AST_PIPE)
		return (exec_pipe(shell, ast));
	if (ast->type == AST_AND)
	{
		if (!exec_ast(shell, ast->left, false))
			return (exec_ast(shell, ast->right, false));
		return (EXIT_FAILURE);
	}
	if (ast->type == AST_OR)
	{
		if (exec_ast(shell, ast->left, false))
			return (exec_ast(shell, ast->right, false));
		return (EXIT_SUCCESS);
	}
	if (ast->type == AST_SUBSHELL)
		return (exec_subshell(shell, ast, in_pipeline));
	return (EXIT_FAILURE);
}
