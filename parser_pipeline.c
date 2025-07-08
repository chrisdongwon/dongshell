/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:41:51 by cwon              #+#    #+#             */
/*   Updated: 2025/07/04 13:53:21 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_argv_list(t_shell *shell, t_ast *ast)
{
	char		*value;
	t_parser	*parser;
	t_token		*token;

	parser = shell->parser;
	while (peek(parser) && peek(parser)->type == TOKEN_WORD)
	{
		token = peek(parser);
		value = token->value;
		if (!append_new_token(&ast->argv_list, value, token->type, \
token->quote))
			flush_and_exit(shell, "append_new_token", EXIT_FAILURE);
		advance(parser);
	}
}

static bool	set_redir_list(t_shell *shell, t_ast *ast)
{
	char			*value;
	t_parser		*parser;
	t_token			*token;
	t_token_type	type;

	parser = shell->parser;
	while (peek(parser) && is_redir(peek(parser)->type))
	{
		type = peek(parser)->type;
		advance(parser);
		if (!peek(parser) || peek(parser)->type != TOKEN_WORD)
		{
			shell->parser->syntax_error = true;
			free(ast);
			return (false);
		}
		token = peek(parser);
		value = token->value;
		if (!append_new_token(&ast->redir_list, value, type, token->quote))
			flush_and_exit(shell, "append_new_token", EXIT_FAILURE);
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
	t_ast		*ast;
	t_parser	*parser;

	parser = shell->parser;
	if (peek(parser) && peek(parser)->type == TOKEN_PAREN_OPEN)
		return (parse_subshell(shell));
	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		flush_and_exit(shell, "ft_calloc", EXIT_FAILURE);
	ast->type = AST_COMMAND;
	set_argv_list(shell, ast);
	if (!set_redir_list(shell, ast))
		return (0);
	return (ast);
}

t_ast	*parse_pipeline(t_shell *shell)
{
	t_ast		*left;
	t_ast		*right;
	t_ast		*ast;
	t_parser	*parser;

	parser = shell->parser;
	if (parser->syntax_error)
		return (0);
	left = parse_command(shell);
	while (match(parser, TOKEN_PIPE))
	{
		right = parse_command(shell);
		ast = new_ast(left, right, AST_PIPE);
		if (!ast)
			flush_and_exit(shell, "new_ast", EXIT_FAILURE);
		left = ast;
	}
	return (left);
}
