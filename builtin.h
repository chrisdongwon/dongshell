/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:22:16 by cwon              #+#    #+#             */
/*   Updated: 2025/07/19 21:53:59 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_list	t_list;
typedef struct s_shell	t_shell;

struct					s_list;
struct					s_shell;

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
size_t		count_builtin_arguments(t_list *argv_list);

#endif
