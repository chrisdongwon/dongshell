/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:37:49 by cwon              #+#    #+#             */
/*   Updated: 2025/07/22 08:34:22 by cwon             ###   ########.fr       */
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
int		exec_builtin_with_redirection(t_shell *shell, t_ast *ast, \
bool in_pipeline);

// executor_command.c
int		exec_command(t_shell *shell, t_ast *ast, bool in_pipeline);

// executor_path.c
char	**get_path_dirs(t_list *envp_list);
char	*check_direct_path(t_shell *shell, const char *command);
char	*search_in_path(t_shell *shell, char **paths, const char *command);

// executor_pipe.c
int		exec_pipe(t_shell *shell, t_ast *ast);

// executor_process.c
int		create_pipe_or_fail(int pipefd[2], int prev_fd);
pid_t	fork_or_fail(int prev_fd, int *pipefd);
void	close_prev_fd(int *prev_fd);
void	safe_execve(t_shell *shell, t_ast *ast, char *pathname);

// executor_redir.c
int		execute_redirection_only(t_shell *shell, t_ast *ast);
void	apply_redirections(t_shell *shell, t_list *redir_list);

// executor_signals.c
int		handle_parent_signals(pid_t pid);

// executor_util.c
char	**list_to_argv_array(t_shell *shell, t_list *argv_list);
void	free_str_array(char **arr);
void	remove_empty_tokens(t_list **argv_list);

// executor.c
int		exec_ast(t_shell *shell, t_ast *ast, bool in_pipeline);

#endif
