/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:36:27 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 12:24:02 by cwon             ###   ########.fr       */
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

static bool	collect_heredoc(t_shell *shell, const char *delim, \
const char *filename)
{
	bool	result;
	int		fd;

	fd = open_heredoc_file(filename);
	if (fd < 0)
		return (false);
	result = true;
	collect_heredoc_loop(shell, &result, fd, delim);
	if (!result)
	{
		if (fd >= 0)
			close(fd);
		unlink(filename);
	}
	else
		close(fd);
	return (result);
}

/**
 * @brief Find the next heredoc token in a redirection list.
 *
 * Iterates through the given linked list of redirection tokens and returns
 * the first token of type TOKEN_HEREDOC found.
 *
 * @param redir_node Pointer to the head of the redirection token list.
 * @return Pointer to the next heredoc token if found, NULL otherwise.
 */
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

/**
 * @brief Process a heredoc by collecting input into a temporary file.
 *
 * Creates a temporary filename based on the given index and collects
 * heredoc input using the given delimiter. Replaces the token's value
 * with the temporary filename on success.
 *
 * @param shell Pointer to the shell state.
 * @param i     Index used for generating a unique temporary filename.
 * @param delim The heredoc delimiter string.
 * @param token Pointer to the heredoc token whose value will be replaced.
 * @return true if heredoc processing succeeded, false otherwise.
 */
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

/**
 * @brief Process all heredocs in an abstract syntax tree (AST).
 *
 * Iterates over the AST's heredoc delimiters and corresponding redirections,
 * processing each heredoc by collecting input and replacing token values
 * with temporary filenames.
 *
 * @param shell Pointer to the shell state.
 * @param ast   Pointer to the AST node containing heredoc information.
 * @param i     Pointer to an integer index used to generate unique filenames.
 */
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
