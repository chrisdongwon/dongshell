/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:27:36 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:49:59 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file envp.h
 * @brief Environment variable management for Minishell.
 *
 * This header defines the structures and functions used for storing,
 * retrieving, and modifying environment variables in the Minishell
 * program. It also provides utilities for converting between linked
 * lists and NULL-terminated arrays.
 */

#ifndef ENVP_H
# define ENVP_H

# include <stdbool.h>

/* Forward declarations */
typedef struct s_envp	t_envp;
typedef struct s_list	t_list;
typedef struct s_shell	t_shell;

struct					s_list;
struct					s_shell;

/**
 * @struct s_envp
 * @brief Represents an environment variable entry.
 *
 * Each environment variable consists of a key, a value, and a flag
 * indicating whether it should be exported to child processes.
 */
struct s_envp
{
	bool	exported;
	char	*key;
	char	*value;
};

/* ====================== envp_array.c ====================== */
/**
 * @brief Converts an environment list to an array.
 *
 * Creates a newly allocated NULL-terminated array of strings in the
 * form "KEY=VALUE" from the given environment list.
 *
 * @param shell Pointer to the shell state.
 * @param node Pointer to the head of the environment variable list.
 * @return Newly allocated NULL-terminated array of strings.
 */
char	**list_to_envp_array(t_shell *shell, t_list *node);

/* ====================== envp_set.c ======================== */
/**
 * @brief Sets or updates an environment variable.
 *
 * If the variable exists, its value is updated. Otherwise, a new
 * variable is created.
 *
 * @param shell Pointer to the shell state.
 * @param key Variable name.
 * @param value Variable value (NULL to unset).
 * @param exported True if the variable should be exported.
 */
void	set_env(t_shell *shell, const char *key, const char *value, \
bool exported);

/* ====================== envp_sort.c ======================== */
/**
 * @brief Sort environment variable list using mergesort.
 * 
 * @param node Head of the environment variable linked list.
 * @return t_list* Sorted linked list head.
 */
t_list	*mergesort_envp(t_list *node);

/* ====================== envp_util.c ======================= */
/**
 * @brief Retrieves the value of an environment variable.
 *
 * @param envp_list Pointer to the environment variable list.
 * @param key Variable name.
 * @return Pointer to the value string, or NULL if not found.
 */
char	*get_envp_value(t_list *envp_list, const char *key);

/**
 * @brief Creates an environment variable from a "KEY=VALUE" string.
 *
 * @param shell Pointer to the shell state.
 * @param envp_str Environment string in "KEY=VALUE" format.
 * @return Pointer to the newly allocated environment variable.
 */
t_envp	*envp_to_node(t_shell *shell, const char *envp_str);

/**
 * @brief Allocates and initializes a new environment variable.
 *
 * @param shell Pointer to the shell state.
 * @param key Variable name.
 * @param value Variable value.
 * @param exported True if the variable should be exported.
 * @return Pointer to the newly allocated environment variable.
 */
t_envp	*new_envp(t_shell *shell, const char *key, const char *value, \
bool exported);

/* ====================== envp.c ============================ */
/**
 * @brief Finds an environment variable by name.
 *
 * @param shell Pointer to the shell state.
 * @param key Variable name.
 * @return Pointer to the environment variable, or NULL if not found.
 */
t_envp	*get_envp(t_shell *shell, const char *key);

/**
 * @brief Frees an environment variable structure.
 *
 * @param arg Pointer to the environment variable to free.
 */
void	free_envp(void *arg);

/**
 * @brief Initializes the shell's environment variable list.
 *
 * Populates the shell's environment variable list from the provided
 * NULL-terminated envp array.
 *
 * @param shell Pointer to the shell state.
 * @param envp NULL-terminated array of environment strings.
 */
void	init_envp(t_shell *shell, char **envp);

#endif /* ENVP_H */
