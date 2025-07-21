/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:07:10 by cwon              #+#    #+#             */
/*   Updated: 2025/07/21 15:42:30 by cwon             ###   ########.fr       */
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
#include "signal_handler.h"

#include "minishell.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*get_command_path(t_shell *shell, t_list *argv, t_list *envp)
{
	char	**paths;
	char	*command;
	char	*result;
	t_token	*token;

	token = (t_token *)argv->content;
	command = token->value;
	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	paths = get_path_dirs(envp);
	if (!paths)
		flush_and_exit(shell, "ft_split", EXIT_FAILURE);
	result = search_in_path(shell, paths, command);
	free_str_array(paths);
	if (!result)
		return (0);
	return (result);
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

static void	exec_or_error(t_shell *shell, t_ast *ast, char *pathname)
{
	struct stat	st;

	if (stat(pathname, &st) < 0)
		flush_and_exit(shell, "stat", 127);
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(pathname, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		flush_and_exit(shell, 0, 126);
	}
	if (access(pathname, X_OK))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(pathname, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		flush_and_exit(shell, 0, 126);
	}
	safe_execve(shell, ast, pathname);
}

static void	exec_command_child_process(t_shell *shell, t_ast *ast)
{
	char	*pathname;

	reset_signal_handlers();
	apply_redirections(shell, ast->redir_list);
	pathname = get_command_path(shell, ast->argv_list, shell->envp_list);
	if (!pathname)
		command_not_found(shell, ast);
	exec_or_error(shell, ast, pathname);
}

int	exec_command(t_shell *shell, t_ast *ast, bool in_pipeline)
{
	pid_t	pid;

	if (!ast || !ast->argv_list || !ast->argv_list->content)
		return (EXIT_SUCCESS);
	remove_empty_tokens(&ast->argv_list);
	if (!ast->argv_list)
		return (EXIT_SUCCESS);
	if (is_builtin(ast->argv_list))
		return (exec_builtin_with_redirection(shell, ast, in_pipeline));
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (!pid)
		exec_command_child_process(shell, ast);
	return (handle_parent_signals(pid));
}
