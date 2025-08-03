/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:04:48 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:00:22 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "ast.h"
#include "libft/libft.h"
#include "minishell.h"
#include "parser.h"

/**
 * @brief Add a heredoc delimiter to an AST command node.
 *
 * Creates a copy of the delimiter string and appends it to the
 * heredoc_delim list in the AST.
 *
 * @param shell Pointer to the shell instance.
 * @param ast   Pointer to the AST command node.
 * @param value String containing the heredoc delimiter.
 *
 * @note On allocation failure, calls flush_and_exit().
 */
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

bool	is_redir(t_token_type type)
{
	return (type == TOKEN_APPEND || type == TOKEN_HEREDOC || \
type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT);
}

bool	validate_redir(t_shell *shell, t_ast *ast)
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

void	process_redir(t_shell *shell, t_ast *ast, t_token *token, \
t_token_type type)
{
	if (type == TOKEN_HEREDOC)
		add_heredoc_delim(shell, ast, token->value);
	if (!append_new_token(&ast->redir_list, token->value, type, token->quote))
		flush_and_exit(shell, "append_new_token", EXIT_FAILURE);
}
