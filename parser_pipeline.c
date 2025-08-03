/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:41:51 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 16:25:07 by cwon             ###   ########.fr       */
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
 * @brief Validate the left-hand side of a pipeline.
 *
 * Checks whether the left-hand side of a pipeline (`left`) is valid 
 * before processing a pipe (`|`) token. This ensures that a pipeline
 * does not begin with a pipe operator or have an empty left-hand 
 * command, which would constitute a syntax error.
 *
 * If a syntax error is detected, the function:
 * - Marks the parser state as having a syntax error.
 * - Frees the provided AST for the left-hand side.
 * - Returns false to indicate failure.
 *
 * @param parser Pointer to the parser state, used to inspect the 
 *               upcoming token and record syntax errors.
 * @param left   Pointer to the AST node representing the left-hand 
 *               side of the pipeline.
 *
 * @return true if the left-hand side is valid and no syntax error 
 *         has occurred; false otherwise.
 */
static bool	check_ast_left(t_parser *parser, t_ast *left)
{
	if (peek(parser) && peek(parser)->type == TOKEN_PIPE && (!left || \
(!left->argv_list && !left->redir_list && left->type != AST_SUBSHELL)))
	{
		parser->syntax_error = true;
		free_ast(left);
		return (false);
	}
	return (left && !parser->syntax_error);
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

bool	set_command_parts(t_shell *shell, t_parser *parser, t_ast *ast)
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

t_ast	*parse_pipeline(t_shell *shell)
{
	t_ast		*left;
	t_ast		*right;
	t_parser	*parser;

	left = parse_command(shell);
	parser = shell->parser;
	if (!check_ast_left(parser, left))
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
