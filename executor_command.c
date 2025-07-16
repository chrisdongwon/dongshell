/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:07:10 by cwon              #+#    #+#             */
/*   Updated: 2025/07/16 15:29:13 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ast.h"
#include "envp.h"
#include "executor.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

static char	*get_command_path(t_shell *shell, t_list *argv, t_list *envp)
{
	char	**paths;
	char	*command;
	char	*result;
	t_token	*token;

	token = (t_token *)argv->content;
	command = token->value;
	result = check_direct_path(shell, command);
	if (result)
		return (result);
	paths = get_path_dirs(envp);
	if (!paths)
		flush_and_exit(shell, "ft_split", EXIT_FAILURE);
	result = search_in_path(shell, paths, command);
	free_str_array(paths);
	return (result);
}

static int	handle_signals(pid_t pid)
{
	int			status;
	t_sigaction	old_int;
	t_sigaction	old_quit;

	ignore_parent_signals(&old_int, &old_quit);
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		restore_parent_signals(&old_int, &old_quit);
		return (EXIT_FAILURE);
	}
	restore_parent_signals(&old_int, &old_quit);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_FAILURE);
}

static void	command_not_found(t_shell *shell, t_ast *ast)
{
	t_token	*token;

	token = (t_token *)ast->argv_list->content;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(token->value, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	flush_and_exit(shell, 0, 127);
}

int	exec_command(t_shell *shell, t_ast *ast)
{
	char	*pathname;
	pid_t	pid;

	if (!ast || !ast->argv_list || !ast->argv_list->content)
		return (EXIT_SUCCESS);
	if (is_builtin(ast->argv_list))
		return (exec_builtin_with_redirection(shell, ast));
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (!pid)
	{
		setup_child_signals();
		pathname = get_command_path(shell, ast->argv_list, shell->envp_list);
		if (!pathname)
			command_not_found(shell, ast);
		apply_redirections(shell, ast->redir_list);
		safe_execve(shell, ast, pathname);
	}
	return (handle_signals(pid));
}
