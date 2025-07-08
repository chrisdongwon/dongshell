/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:37:49 by cwon              #+#    #+#             */
/*   Updated: 2025/07/08 14:40:29 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <linux/limits.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>

# include "envp.h"
# include "expander.h"

// builtin_cd.c
int			builtin_cd(t_shell *shell, t_list *argv_list);

// builtin_echo.c
int			builtin_echo(t_list *argv_list);

// builtin_env.c
int			builtin_env(t_shell *shell);

// builtin_exit_util.c
bool		is_numeric_long(const char *str);
long		str_to_long(const char *str);

// builtin_exit.c
int			builtin_exit(t_shell *shell, t_list *argv_list);

// builtin_export_sort.c
t_list		*mergesort_envp(t_list *node);

// builtin_export_util.c
void		print_sorted_env(t_shell *shell);

// builtin_export.c
int			builtin_export(t_shell *shell, t_list *argv_list);

// builtin_pwd.c
int			builtin_pwd(void);

// builtin_unset.c
int			builtin_unset(t_shell *shell, t_list *argv_list);

// builtin_util.c
char		*escape_value(const char *value);
const char	*get_argv_value(t_list *argv_list, int index);

// executor_builtin.c
bool		is_builtin(t_list *argv_list);
int			exec_builtin(t_shell *shell, t_list *argv_list);

// executor.c
int			exec_ast(t_shell *shell, t_ast *ast);

// minishell.c
void		flush_shell(t_shell *shell);

#endif
