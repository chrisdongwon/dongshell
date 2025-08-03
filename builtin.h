/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:22:16 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:44:17 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin.h
 * @brief Declarations for builtin shell commands and related utilities.
 *
 * This header declares builtin command functions such as cd, echo, env, exit,
 * export, pwd, unset, and related utility functions used by the shell.
 */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdbool.h>
# include <stddef.h>

/* Forward declarations */
typedef struct s_list	t_list;
typedef struct s_shell	t_shell;

struct					s_list;
struct					s_shell;

/* ================= builtin_cd.c ================= */
/**
 * @brief Change the current working directory.
 * 
 * @param shell     Pointer to shell state.
 * @param argv_list List of command arguments.
 * @return int Exit status code.
 */
int			builtin_cd(t_shell *shell, t_list *argv_list);

/* ================= builtin_echo.c ================= */
/**
 * @brief Print arguments to standard output.
 * 
 * @param argv_list List of command arguments.
 * @return int Exit status code.
 */
int			builtin_echo(t_list *argv_list);

/* ================= builtin_env.c ================= */
/**
 * @brief Print environment variables.
 * 
 * @param shell Pointer to shell state.
 * @return int Exit status code.
 */
int			builtin_env(t_shell *shell);

/* ================= builtin_exit_util.c ================= */
/**
 * @brief Check if a string represents a valid numeric long.
 * 
 * @param str Input string.
 * @return true if string is numeric long, false otherwise.
 */
bool		is_numeric_long(const char *str);
/**
 * @brief Convert a string to a long integer.
 * 
 * @param str Input string.
 * @return long Converted long value.
 */
long		str_to_long(const char *str);

/* ================= builtin_exit.c ================= */
/**
 * @brief Exit the shell with an optional status code.
 * 
 * @param shell     Pointer to shell state.
 * @param argv_list List of command arguments.
 * @return int Exit status code (does not return on success).
 */
int			builtin_exit(t_shell *shell, t_list *argv_list);

/* ================= builtin_export_util.c ================= */
/**
 * @brief Print environment variables sorted alphabetically.
 * 
 * @param shell Pointer to shell state.
 */
void		print_sorted_env(t_shell *shell);

/* ================= builtin_export.c ================= */
/**
 * @brief Export or update environment variables.
 * 
 * @param shell     Pointer to shell state.
 * @param argv_list List of command arguments.
 * @return int Exit status code.
 */
int			builtin_export(t_shell *shell, t_list *argv_list);

/* ================= builtin_pwd.c ================= */
/**
 * @brief Print the current working directory.
 * 
 * @return int Exit status code.
 */
int			builtin_pwd(void);

/* ================= builtin_unset.c ================= */
/**
 * @brief Remove environment variables.
 * 
 * @param shell     Pointer to shell state.
 * @param argv_list List of command arguments.
 * @return int Exit status code.
 */
int			builtin_unset(t_shell *shell, t_list *argv_list);

/* ================= builtin_util.c ================= */
/**
 * @brief Create an escaped copy of a string.
 *
 * This function allocates and returns a new string where double quotes (`"`),
 * dollar signs (`$`), and backslashes (`\`) are escaped with a backslash.
 * If the input is `NULL`, an empty string is returned.
 *
 * @param value The string to escape (can be NULL).
 * @return char* Newly allocated escaped string, or NULL on allocation failure.
 *         Caller is responsible for freeing the returned string.
 */
char		*escape_value(const char *value);

/**
 * @brief Get the value of an argument at a given index.
 * 
 * @param argv_list List of command arguments.
 * @param index     Argument index.
 * @return const char* Argument value or NULL if out of bounds.
 */
const char	*get_argv_value(t_list *argv_list, int index);

/**
 * @brief Count the number of arguments in a builtin command.
 * 
 * @param argv_list List of command arguments.
 * @return size_t Number of arguments.
 */
size_t		count_builtin_arguments(t_list *argv_list);

#endif /* BUILTIN_H */
