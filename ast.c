/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:08:45 by cwon              #+#    #+#             */
/*   Updated: 2025/07/19 23:48:35 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "lexer.h"
#include "libft/libft.h"

t_ast	*new_ast(t_ast *left, t_ast *right, t_ast_type type)
{
	t_ast	*result;

	result = malloc(sizeof(t_ast));
	if (!result)
	{
		free_ast(left);
		free_ast(right);
		return (0);
	}
	result->heredoc_delim = 0;
	result->type = type;
	result->left = left;
	result->right = right;
	result->argv_list = 0;
	result->redir_list = 0;
	return (result);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	free_ast(ast->left);
	free_ast(ast->right);
	ft_lstclear(&ast->argv_list, free_token);
	ft_lstclear(&ast->heredoc_delim, free);
	ft_lstclear(&ast->redir_list, free_token);
	free(ast);
}
