/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:37:33 by cwon              #+#    #+#             */
/*   Updated: 2025/07/07 21:05:37 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

bool	is_builtin(t_list *argv_list)
{
	char	*cmd;
	t_token	*token;

	if (!argv_list)
		return (false);
	token = (t_token *)argv_list->content;
	cmd = token->value;
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || \
!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit") || \
!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "pwd") || \
!ft_strcmp(cmd, "unset"));
}

int	exec_builtin(t_shell *shell, t_list *argv_list)
{
	char	*cmd;
	t_token	*token;

	token = (t_token *)argv_list->content;
	cmd = token->value;
	if (!ft_strcmp(cmd, "cd"))
		return (builtin_cd(shell, argv_list));
	if (!ft_strcmp(cmd, "echo"))
		return (builtin_echo(argv_list));
	if (!ft_strcmp(cmd, "env"))
		return (builtin_env(shell));
	if (!ft_strcmp(cmd, "exit"))
		return (builtin_exit(shell, argv_list));
	if (!ft_strcmp(cmd, "export"))
		return (builtin_export(shell, argv_list));
	if (!ft_strcmp(cmd, "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd, "unset"))
		return (builtin_unset(shell, argv_list));
	return (EXIT_FAILURE);
}
