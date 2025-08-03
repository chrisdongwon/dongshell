/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:30:49 by cwon              #+#    #+#             */
/*   Updated: 2025/08/01 15:32:46 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file minishell.h
 * @brief Main header file for the Minishell project.
 *
 * This header defines the core data structures and function prototypes
 * used by the Minishell program, including the shell state, parser, lexer,
 * expander, and AST (Abstract Syntax Tree) components for debugging.
 */

#ifndef MINISHELL_H
# define MINISHELL_H

/** Forward declarations for main project structures. */
typedef struct s_ast		t_ast;
typedef struct s_expander	t_expander;
typedef struct s_lexer		t_lexer;
typedef struct s_list		t_list;
typedef struct s_parser		t_parser;
typedef struct s_shell		t_shell;

struct						s_ast;
struct						s_expander;
struct						s_lexer;
struct						s_list;
struct						s_parser;

/**
 * @struct s_shell
 * @brief Stores the current state of the shell.
 *
 * This structure contains the shell's runtime information, including
 * the current command, prompt, exit status of the last process,
 * environment variables, and subsystems for lexing, parsing, and expanding.
 */
struct s_shell
{
	char		*command;
	char		*prompt;
	int			last_exit_status;
	t_expander	*expander;
	t_lexer		*lexer;
	t_list		*envp_list;
	t_parser	*parser;
};

/* ======================== minishell_print.c ======================== */

/**
 * @brief Prints the content of a token (debugging).
 *
 * @param arg Pointer to the token to print.
 */
void	print_token(void *arg);

/**
 * @brief Recursively prints the Abstract Syntax Tree (debugging).
 *
 * @param ast Pointer to the AST root node.
 * @param indent Indentation level for formatted output.
 */
void	print_ast(t_ast *ast, int indent);

/* ======================= minishell_prompt.c ======================= */

/**
 * @brief Reads a command from user input.
 *
 * @param shell Pointer to the shell state.
 */
void	read_command(t_shell *shell);

/* =========================== minishell.c =========================== */

/**
 * @brief Cleans up resources and exits the shell.
 *
 * @param shell Pointer to the shell state.
 * @param error_msg Error message to print before exiting (can be NULL).
 * @param exit_status Exit code returned to the operating system.
 */
void	flush_and_exit(t_shell *shell, const char *error_msg, int exit_status);

/**
 * @brief Starts the main shell loop.
 *
 * Initializes the shell, processes commands, and manages subsystems
 * until the user exits.
 *
 * @param envp Null-terminated array of environment variables.
 */
void	minishell(char **envp);

#endif /* MINISHELL_H */
