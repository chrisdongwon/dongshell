/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:11 by cwon              #+#    #+#             */
/*   Updated: 2025/07/27 17:40:02 by cwon             ###   ########.fr       */
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
