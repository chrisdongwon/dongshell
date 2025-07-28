/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:36:27 by cwon              #+#    #+#             */
/*   Updated: 2025/07/28 15:10:07 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "expander.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

static t_token	*find_next_heredoc_token(t_list *redir_node)
{
	t_token	*token;

	while (redir_node)
	{
		token = redir_node->content;
		if (token->type == TOKEN_HEREDOC)
			return (token);
		redir_node = redir_node->next;
	}
	return (0);
}

static bool	process_heredoc(t_shell *shell, int i, const char *delim, \
t_token *token)
{
	char	*temp_filename;

	temp_filename = make_temp_filename(i);
	if (!temp_filename)
		return (false);
	if (!collect_heredoc(shell, delim, temp_filename))
	{
		free(temp_filename);
		return (false);
	}
	free(token->value);
	token->value = temp_filename;
	return (true);
}

// should delim be a token to track if quotes are used, or does it not matter?
static void	process_ast_heredocs(t_shell *shell, t_ast *ast, int *i)
{
	char	*delim;
	t_list	*delim_node;
	t_list	*redir_node;
	t_token	*token;

	delim_node = ast->heredoc_delim;
	redir_node = ast->redir_list;
	while (delim_node)
	{
		delim = delim_node->content;
		token = find_next_heredoc_token(redir_node);
		if (!token)
			flush_and_exit(shell, "find_next_heredoc_token", EXIT_FAILURE);
		if (!process_heredoc(shell, (*i)++, delim, token))
			flush_and_exit(shell, "process_heredoc", EXIT_FAILURE);
		delim_node = delim_node->next;
		if (redir_node)
			redir_node = redir_node->next;
	}
}

void	prepare_heredocs(t_shell *shell, t_ast *ast, int *i)
{
	if (!ast)
		return ;
	if (ast->type == AST_COMMAND)
		process_ast_heredocs(shell, ast, i);
	else
	{
		prepare_heredocs(shell, ast->left, i);
		prepare_heredocs(shell, ast->right, i);
	}
}
