/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:06:21 by cwon              #+#    #+#             */
/*   Updated: 2025/05/20 19:45:15 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"

typedef enum e_ast_type	t_ast_type;
typedef struct s_ast	t_ast;

enum e_ast_type
{
	AST_AND,
	AST_COMMAND,
	AST_OR,
	AST_PIPE,
	AST_SUBSHELL
};

struct s_ast
{
	t_ast		*left;
	t_ast		*right;
	t_ast_type	type;
	t_list		*argv_list;
	t_list		*redir_list;
};

// ast.c
t_ast	*new_ast(t_ast *left, t_ast *right, t_ast_type type);
void	free_ast(t_ast *ast);

#endif
