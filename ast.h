/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:06:21 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:04:13 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ast.h
 * @brief Abstract Syntax Tree (AST) definitions for the shell parser.
 *
 * This module defines the data structures and functions for
 * representing and managing the parsed command syntax tree.
 */

#ifndef AST_H
# define AST_H

/* Forward declarations */
typedef enum e_ast_type	t_ast_type;
typedef struct s_ast	t_ast;
typedef struct s_list	t_list;

struct					s_list;

/**
 * @enum e_ast_type
 * @brief Enumeration of AST node types.
 *
 * Defines the types of operations or constructs represented
 * in the AST.
 */
enum e_ast_type
{
	AST_AND,
	AST_COMMAND,
	AST_OR,
	AST_PIPE,
	AST_SUBSHELL
};

/**
 * @struct s_ast
 * @brief Represents a node in the Abstract Syntax Tree.
 *
 * Each AST node can have left and right children (for binary
 * operations), a type indicating the operation or command, and
 * lists for arguments, redirections, and heredoc delimiters.
 */
struct s_ast
{
	t_ast		*left;
	t_ast		*right;
	t_ast_type	type;
	t_list		*argv_list;
	t_list		*heredoc_delim;
	t_list		*redir_list;
};

/* ================= ast.c ================= */

/**
 * @brief Create a new AST node.
 *
 * Allocates and initializes a new AST node with the given left
 * and right children and node type.
 *
 * @param left  Pointer to the left child AST node.
 * @param right Pointer to the right child AST node.
 * @param type  Type of the AST node.
 *
 * @return Pointer to the newly allocated AST node, or NULL on
 *         failure.
 */
t_ast	*new_ast(t_ast *left, t_ast *right, t_ast_type type);

/**
 * @brief Free an AST and all its children.
 *
 * Recursively frees the given AST node and all associated
 * dynamically allocated data.
 *
 * @param ast Pointer to the AST node to free.
 */
void	free_ast(t_ast *ast);

#endif /* AST_H */
