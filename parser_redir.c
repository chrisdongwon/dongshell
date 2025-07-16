/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:04:48 by cwon              #+#    #+#             */
/*   Updated: 2025/07/12 21:34:45 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "ast.h"
#include "libft/libft.h"
#include "minishell.h"
#include "parser.h"

static bool	is_redir(t_token_type type)
{
	return (type == TOKEN_APPEND || type == TOKEN_HEREDOC || \
type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT);
}

static bool	validate_redir(t_shell *shell, t_ast *ast)
{
	t_parser	*parser;

	parser = shell->parser;
	if (!peek(parser) || peek(parser)->type != TOKEN_WORD)
	{
		shell->parser->syntax_error = true;
		free(ast);
		return (false);
	}
	return (true);
}

static void	add_heredoc_delim(t_shell *shell, t_ast *ast, const char *value)
{
	char	*delim;
	t_list	*node;

	delim = ft_strdup(value);
	if (!delim)
		flush_and_exit(shell, "ft_strdup", EXIT_FAILURE);
	node = ft_lstnew(delim);
	if (!node)
	{
		free(delim);
		flush_and_exit(shell, "ft_lstnew", EXIT_FAILURE);
	}
	ft_lstadd_back(&ast->heredoc_delim, node);
}

static void	process_redir(t_shell *shell, t_ast *ast, t_token *token, \
t_token_type type)
{
	if (type == TOKEN_HEREDOC)
		add_heredoc_delim(shell, ast, token->value);
	if (!append_new_token(&ast->redir_list, token->value, type, token->quote))
		flush_and_exit(shell, "append_new_token", EXIT_FAILURE);
}

bool	set_redir_list(t_shell *shell, t_ast *ast)
{
	t_parser		*parser;
	t_token			*token;
	t_token_type	type;

	parser = shell->parser;
	while (peek(parser) && is_redir(peek(parser)->type))
	{
		type = peek(parser)->type;
		advance(parser);
		if (!validate_redir(shell, ast))
			return (false);
		token = peek(parser);
		process_redir(shell, ast, token, type);
		advance(parser);
	}
	return (true);
}
