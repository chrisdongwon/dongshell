/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:34:35 by cwon              #+#    #+#             */
/*   Updated: 2025/07/08 14:49:45 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	exec_command(t_shell *shell, t_ast *ast)
{
	if (is_builtin(ast->argv_list))
		return (exec_builtin(shell, ast->argv_list));
	printf("function is not builtin\n");
	return (EXIT_SUCCESS);
}

int	exec_ast(t_shell *shell, t_ast *ast)
{
	if (!ast)
		return (EXIT_SUCCESS);
	if (ast->type == AST_COMMAND)
		return (exec_command(shell, ast));
	// if (ast->type == AST_PIPE)
	// 	return (exec_pipe(shell, ast));
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
	// if (ast->type == AST_SUBSHELL)
	// 	return (exec_subshell(shell, ast));
	return (EXIT_FAILURE);
}
