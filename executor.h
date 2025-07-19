/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:37:49 by cwon              #+#    #+#             */
/*   Updated: 2025/07/19 22:37:55 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdbool.h>

typedef struct s_ast		t_ast;
typedef struct s_list		t_list;
typedef struct s_shell		t_shell;
typedef struct sigaction	t_sigaction;

struct						s_ast;
struct						s_list;
struct						s_shell;

// executor_builtin.c
bool	is_builtin(t_list *argv_list);
int		exec_builtin_with_redirection(t_shell *shell, t_ast *ast);

// executor_command.c
int		exec_command(t_shell *shell, t_ast *ast);

// executor_path.c
char	**get_path_dirs(t_list *envp_list);
char	*check_direct_path(t_shell *shell, const char *command);
char	*search_in_path(t_shell *shell, char **paths, const char *command);

// executor_pipe.c
int		exec_pipe(t_shell *shell, t_ast *ast);

// executor_process.c
bool	safe_pipe(int pipefd[2], int prev_fd);
void	safe_close(int fd);
void	safe_execve(t_shell *shell, t_ast *ast, char *pathname);

// executor_redir.c
void	apply_redirections(t_shell *shell, t_list *redir_list);

// executor_signals.c
void	ignore_parent_signals(t_sigaction *old_int, t_sigaction *old_quit);
void	restore_parent_signals(t_sigaction *old_int, t_sigaction *old_quit);

// executor_util.c
bool	safe_pipe(int pipefd[2], int prev_fd);
char	**list_to_argv_array(t_shell *shell, t_list *argv_list);
void	free_str_array(char **arr);
void	safe_close(int fd);

// executor.c
int		exec_ast(t_shell *shell, t_ast *ast);

#endif
