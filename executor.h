/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:37:49 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:23:49 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor.h
 * @brief Declarations for shell command execution functions and utilities.
 *
 * This header provides function prototypes for executing commands,
 * handling builtins, managing pipes and redirections, process control,
 * and signal handling in the shell.
 */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdbool.h>

/* Forward declarations */

typedef struct s_ast		t_ast;
typedef struct s_list		t_list;
typedef struct s_shell		t_shell;
typedef struct sigaction	t_sigaction;

struct						s_ast;
struct						s_list;
struct						s_shell;

/* ====================== executor_builtin.c ====================== */
/**
 * @brief Checks if the given command is a shell builtin.
 *
 * @param argv_list List of command arguments.
 * @return true if the command is a builtin, false otherwise.
 */
bool	is_builtin(t_list *argv_list);

/**
 * @brief Executes a builtin command with applied redirections.
 *
 * @param shell Pointer to shell state.
 * @param ast   AST node representing the command.
 * @param in_pipeline True if command is part of a pipeline.
 * @return Exit status of the builtin command.
 */
int		exec_builtin_with_redirection(t_shell *shell, t_ast *ast, \
bool in_pipeline);

/* ====================== executor_command.c ====================== */
/**
 * @brief Executes an external command.
 *
 * @param shell Pointer to shell state.
 * @param ast   AST node representing the command.
 * @param in_pipeline True if command is part of a pipeline.
 * @return Exit status of the command.
 */
int		exec_command(t_shell *shell, t_ast *ast, bool in_pipeline);

/* ====================== executor_path.c ====================== */
/**
 * @brief Retrieves PATH directories from the environment.
 *
 * @param envp_list List of environment variables.
 * @return Array of directory strings (NULL-terminated).
 */
char	**get_path_dirs(t_list *envp_list);

/**
 * @brief Checks if the command is a direct executable path.
 *
 * @param shell Pointer to shell state.
 * @param command Command string.
 * @return Full path to executable if valid, NULL otherwise.
 */
char	*check_direct_path(t_shell *shell, const char *command);

/**
 * @brief Searches for the command in given PATH directories.
 *
 * @param shell Pointer to shell state.
 * @param paths Array of directories to search.
 * @param command Command name to search for.
 * @return Full path to executable if found, NULL otherwise.
 */
char	*search_in_path(t_shell *shell, char **paths, const char *command);

/* ====================== executor_pipe.c ====================== */
/**
 * @brief Executes commands connected by pipes.
 *
 * @param shell Pointer to shell state.
 * @param ast   AST node representing the pipeline.
 * @return Exit status of the pipeline execution.
 */
int		exec_pipe(t_shell *shell, t_ast *ast);

/* ====================== executor_process.c ====================== */
/**
 * @brief Creates a pipe or exits on failure.
 *
 * @param pipefd Array to hold the pipe file descriptors.
 * @param prev_fd File descriptor from the previous command.
 * @return 0 on success, exits on failure.
 */
int		create_pipe_or_fail(int pipefd[2], int prev_fd);

/**
 * @brief Forks a new process or exits on failure.
 *
 * @param prev_fd File descriptor from the previous command.
 * @param pipefd Array of pipe file descriptors.
 * @return PID of child process.
 */
pid_t	fork_or_fail(int prev_fd, int *pipefd);

/**
 * @brief Closes the previous file descriptor safely.
 *
 * @param prev_fd Pointer to the previous file descriptor.
 */
void	close_prev_fd(int *prev_fd);

/**
 * @brief Executes the command with execve, handling errors safely.
 *
 * @param shell Pointer to shell state.
 * @param ast AST node representing the command.
 * @param pathname Path to the executable.
 */
void	safe_execve(t_shell *shell, t_ast *ast, char *pathname);

/* ====================== executor_redir.c ====================== */
/**
 * @brief Executes only the redirections for a command.
 *
 * @param shell Pointer to shell state.
 * @param ast AST node representing the command.
 * @return 0 on success, nonzero on failure.
 */
int		execute_redirection_only(t_shell *shell, t_ast *ast);

/**
 * @brief Applies the redirections described in the redirection list.
 *
 * @param shell Pointer to shell state.
 * @param redir_list List of redirection tokens.
 */
void	apply_redirections(t_shell *shell, t_list *redir_list);

/* ====================== executor_signals.c ====================== */
/**
 * @brief Handles signals in the parent process after fork.
 *
 * @param pid PID of the child process.
 * @return Exit status of the child or signal indication.
 */
int		handle_parent_signals(pid_t pid);

/* ====================== executor_util.c ====================== */
/**
 * @brief Converts a linked list of arguments to a NULL-terminated argv array.
 *
 * @param shell Pointer to shell state.
 * @param argv_list Linked list of argument tokens.
 * @return Newly allocated argv array.
 */
char	**list_to_argv_array(t_shell *shell, t_list *argv_list);

/**
 * @brief Frees a NULL-terminated array of strings.
 *
 * @param arr Array of strings to free.
 */
void	free_str_array(char **arr);

/**
 * @brief Removes empty tokens from the argument list.
 *
 * @param argv_list Pointer to the argument list to clean.
 */
void	remove_empty_tokens(t_list **argv_list);

/* ====================== executor.c ====================== */
/**
 * @brief Executes an AST node representing a command or pipeline.
 *
 * @param shell Pointer to shell state.
 * @param ast AST node to execute.
 * @param in_pipeline True if part of a pipeline.
 * @return Exit status code.
 */
int		exec_ast(t_shell *shell, t_ast *ast, bool in_pipeline);

/**
 * @brief Main entry to execute a command after parsing.
 *
 * @param shell Pointer to shell state.
 */
void	execute_command(t_shell *shell);

#endif /* EXECUTOR_H */
