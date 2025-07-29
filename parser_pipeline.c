/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:41:51 by cwon              #+#    #+#             */
/*   Updated: 2025/07/29 15:01:22 by cwon             ###   ########.fr       */
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

static bool	set_command_parts(t_shell *shell, t_parser *parser, t_ast *ast)
{
	t_token			*token;
	t_token_type	type;

	while (peek(parser))
	{
		token = peek(parser);
		if (token->type == TOKEN_WORD)
			add_token_to_argv(shell, &ast->argv_list, token);
		else if (is_redir(token->type))
		{
			type = token->type;
			advance(parser);
			if (!validate_redir(shell, ast))
				return (false);
			token = peek(parser);
			process_redir(shell, ast, token, type);
		}
		else
			break ;
		advance(parser);
	}
	return (true);
}

static t_ast	*parse_subshell(t_shell *shell)
{
	t_ast		*ast;
	t_ast		*subshell;
	t_parser	*parser;

	parser = shell->parser;
	if (parser->syntax_error || !match(parser, TOKEN_PAREN_OPEN))
		return (0);
	subshell = parse(shell);
	if (!match(parser, TOKEN_PAREN_CLOSE))
	{
		parser->syntax_error = true;
		return (0);
	}
	ast = new_ast(subshell, 0, AST_SUBSHELL);
	if (!ast)
		flush_and_exit(shell, "new_ast", EXIT_FAILURE);
	return (ast);
}

static t_ast	*parse_command(t_shell *shell)
{
	t_parser	*parser;
	t_ast		*ast;

	parser = shell->parser;
	if (peek(parser) && peek(parser)->type == TOKEN_PAREN_OPEN)
		return (parse_subshell(shell));
	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		flush_and_exit(shell, "ft_calloc", EXIT_FAILURE);
	ast->type = AST_COMMAND;
	if (!set_command_parts(shell, shell->parser, ast))
		return (0);
	return (ast);
}

static t_ast	*parse_pipe_operands(t_shell *shell, t_ast *left)
{
	t_ast		*ast;
	t_ast		*right;
	t_parser	*parser;

	parser = shell->parser;
	while (match(parser, TOKEN_PIPE))
	{
		right = parse_command(shell);
		if (right && !right->argv_list && !right->redir_list)
		{
			parser->syntax_error = true;
			return (0);
		}
		ast = new_ast(left, right, AST_PIPE);
		if (!ast)
			flush_and_exit(shell, "new_ast", EXIT_FAILURE);
		left = ast;
	}
	return (left);
}

t_ast	*parse_pipeline(t_shell *shell)
{
	t_ast		*left;
	t_parser	*parser;

	parser = shell->parser;
	if (parser->syntax_error)
		return (0);
	left = parse_command(shell);
	if (left && !left->argv_list && !left->redir_list)
	{
		if (peek(parser) && peek(parser)->type == TOKEN_PIPE)
			parser->syntax_error = true;
		return (0);
	}
	return (parse_pipe_operands(shell, left));
}
