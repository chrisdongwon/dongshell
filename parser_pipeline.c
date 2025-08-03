/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:41:51 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:00:53 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

#include "ast.h"
#include "libft/libft.h"
#include "minishell.h"
#include "parser.h"
#include "envp.h"

/**
 * @brief Free an AST and return NULL.
 *
 * Helper function for error handling that releases the AST
 * memory and returns a NULL pointer.
 *
 * @param ast Pointer to the AST to free.
 * @return Always returns NULL.
 */
static t_ast	*free_ast_return_null(t_ast *ast)
{
	free_ast(ast);
	return (0);
}

/**
 * @brief Parse the parts of a command into an AST node.
 *
 * Reads tokens from the parser and populates the AST with
 * arguments and redirections until no more valid tokens remain.
 *
 * @param shell  Pointer to the shell instance.
 * @param parser Pointer to the parser state.
 * @param ast    Pointer to the AST command node to populate.
 *
 * @return true if parsing succeeded, false on syntax error.
 */
static bool	set_command_parts(t_shell *shell, t_parser *parser, t_ast *ast)
{
	t_token			*token;
	t_token_type	type;

	token = peek(parser);
	while (token)
	{
		if (token->type == TOKEN_WORD)
			add_token_to_argv(shell, &ast->argv_list, token);
		else if (is_redir(token->type))
		{
			type = token->type;
			advance(parser);
			token = peek(parser);
			if (!token || token->type != TOKEN_WORD)
				return (parser_syntax_error(parser));
			if (!validate_redir(shell, ast))
				return (false);
			process_redir(shell, ast, token, type);
		}
		else
			break ;
		advance(parser);
		token = peek(parser);
	}
	return (true);
}

/**
 * @brief Parse a subshell command.
 *
 * Parses commands enclosed in parentheses and returns an AST
 * node of type AST_SUBSHELL.
 *
 * @param shell Pointer to the shell instance.
 * @return Pointer to the AST node, or NULL on error.
 */
static t_ast	*parse_subshell(t_shell *shell)
{
	t_ast		*ast;
	t_ast		*inner;
	t_parser	*parser;

	parser = shell->parser;
	if (!match(parser, TOKEN_PAREN_OPEN))
		return (0);
	inner = parse_and_or(shell);
	if (!inner || parser->syntax_error)
		return (free_ast_return_null(inner));
	if (!match(parser, TOKEN_PAREN_CLOSE))
	{
		parser->syntax_error = true;
		return (free_ast_return_null(inner));
	}
	ast = new_ast(inner, 0, AST_SUBSHELL);
	if (!ast)
		flush_and_exit(shell, "new_ast", EXIT_FAILURE);
	if (!set_command_parts(shell, parser, ast))
		return (free_ast_return_null(ast));
	return (ast);
}

/**
 * @brief Parse a single command or subshell.
 *
 * Allocates and returns an AST node for a simple command or
 * subshell, populating it with arguments and redirections.
 *
 * @param shell Pointer to the shell instance.
 * @return Pointer to the AST node, or NULL on error.
 */
static t_ast	*parse_command(t_shell *shell)
{
	t_ast		*ast;
	t_parser	*parser;

	parser = shell->parser;
	if (peek(parser) && peek(parser)->type == TOKEN_PAREN_OPEN)
		return (parse_subshell(shell));
	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		flush_and_exit(shell, "ft_calloc", EXIT_FAILURE);
	ast->type = AST_COMMAND;
	if (!set_command_parts(shell, parser, ast))
	{
		free_ast(ast);
		return (0);
	}
	return (ast);
}

t_ast	*parse_pipeline(t_shell *shell)
{
	t_ast		*left;
	t_ast		*right;
	t_parser	*parser;

	left = parse_command(shell);
	parser = shell->parser;
	if (!left || parser->syntax_error)
		return (0);
	while (match(parser, TOKEN_PIPE))
	{
		right = parse_command(shell);
		if (!right || \
(!right->argv_list && !right->redir_list && right->type != AST_SUBSHELL))
		{
			parser->syntax_error = true;
			free_ast(left);
			free_ast(right);
			return (0);
		}
		left = new_ast(left, right, AST_PIPE);
		if (!left)
			flush_and_exit(shell, "new_ast", EXIT_FAILURE);
	}
	return (left);
}
