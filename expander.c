/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:11 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:12:54 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "envp.h"
#include "expander.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"
#include "parser.h"

/**
 * @brief Expand variables and wildcards in a token list.
 *
 * Iterates over the token list, expands shell variables in tokens not
 * quoted by single quotes. If the token is part of argv and IFS is set,
 * performs field splitting. After variable expansion, performs wildcard
 * expansion on the list unless a substitution error occurred.
 *
 * @param shell  Pointer to the shell state.
 * @param list   Pointer to the list of tokens to expand.
 * @param is_argv Indicates if the list represents argv tokens (true) or
 *                redirections (false).
 */
static void	expand_list(t_shell *shell, t_list **list, bool is_argv)
{
	t_list	*node;
	t_token	*token;

	node = *list;
	while (node)
	{
		token = (t_token *)node->content;
		if (token->quote != '\'' && ft_strstr(token->value, "$"))
		{
			expand_variable(shell, token);
			if (!token->quote && is_argv && shell->expander->ifs)
				expand_split(shell, list, &node);
		}
		node = node->next;
	}
	if (!shell->expander->sub_error)
		expand_wildcard_list(shell, list, is_argv);
}

/**
 * @brief Recursively expand all tokens in the AST.
 *
 * Expands variable and wildcard tokens in command argument and
 * redirection lists of the AST nodes. Recurses into left and right
 * child nodes for compound commands.
 *
 * @param shell Pointer to the shell state.
 * @param ast   Pointer to the AST node to expand.
 */
static void	expand_ast(t_shell *shell, t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == AST_COMMAND)
	{
		if (ast->argv_list)
			expand_list(shell, &ast->argv_list, true);
		if (ast->redir_list)
			expand_list(shell, &ast->redir_list, false);
	}
	expand_ast(shell, ast->left);
	expand_ast(shell, ast->right);
}

/**
 * @brief Initialize the expander state in the shell.
 *
 * Allocates and initializes the expander structure with references
 * to the current AST, environment variables, last exit status, and
 * sets the IFS value from the environment or defaults to space,
 * tab, and newline if unset.
 *
 * @param shell Pointer to the shell state.
 */
static void	init_expander(t_shell *shell)
{
	shell->expander = malloc(sizeof(t_expander));
	if (!shell->expander)
		flush_and_exit(shell, "malloc", EXIT_FAILURE);
	shell->expander->sub_error = false;
	shell->expander->last_exit_status = shell->last_exit_status;
	shell->expander->ast = shell->parser->ast;
	shell->expander->envp_list = shell->envp_list;
	shell->expander->ifs = get_envp_value(shell->envp_list, "IFS");
	if (!shell->expander->ifs)
		shell->expander->ifs = " \t\n";
}

bool	expander(t_shell *shell)
{
	int	heredoc_index;

	heredoc_index = 0;
	init_expander(shell);
	expand_ast(shell, shell->expander->ast);
	if (shell->expander->sub_error)
	{
		shell->last_exit_status = EXIT_FAILURE;
		return (false);
	}
	prepare_heredocs(shell, shell->expander->ast, &heredoc_index);
	if (shell->expander->sub_error)
	{
		shell->last_exit_status = EXIT_FAILURE;
		return (false);
	}
	return (true);
}

void	flush_expander(t_shell *shell)
{
	free(shell->expander);
	shell->expander = 0;
}
