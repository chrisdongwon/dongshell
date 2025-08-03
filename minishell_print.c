/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 08:35:24 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 10:53:34 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ast.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

/**
 * @brief Convert a token type to its string representation.
 *
 * Maps a token type enum value to a corresponding string for
 * debugging and display purposes.
 *
 * @param type The token type to convert.
 * @return A constant string representing the token type. If the
 *         type is unrecognized, returns "UNKNOWN_TOKEN_TYPE".
 */
static const char	*token_type_str(t_token_type type)
{
	if (type == TOKEN_AND)
		return ("TOKEN_AND");
	else if (type == TOKEN_APPEND)
		return ("TOKEN_APPEND");
	else if (type == TOKEN_END)
		return ("TOKEN_END");
	else if (type == TOKEN_ERROR)
		return ("TOKEN_ERROR");
	else if (type == TOKEN_HEREDOC)
		return ("TOKEN_HEREDOC");
	else if (type == TOKEN_OR)
		return ("TOKEN_OR");
	else if (type == TOKEN_PAREN_CLOSE)
		return ("TOKEN_PAREN_CLOSE");
	else if (type == TOKEN_PAREN_OPEN)
		return ("TOKEN_PAREN_OPEN");
	else if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	else if (type == TOKEN_REDIR_IN)
		return ("TOKEN_REDIR_IN");
	else if (type == TOKEN_REDIR_OUT)
		return ("TOKEN_REDIR_OUT");
	else if (type == TOKEN_WORD)
		return ("TOKEN_WORD");
	return ("UNKNOWN_TOKEN_TYPE");
}

/**
 * @brief Print details of a command AST node.
 *
 * Displays the command's arguments and any redirections with
 * indentation for readability. Uses token_type_str() to display
 * redirection types as strings.
 *
 * @param ast    Pointer to the AST node of type AST_COMMAND.
 * @param indent Indentation level for pretty-printing output.
 */
static void	print_command(t_ast *ast, int indent)
{
	int		j;
	t_list	*r;
	t_token	*redir;

	printf("COMMAND:");
	ft_lstiter(ast->argv_list, print_token);
	printf("\n");
	r = ast->redir_list;
	while (r)
	{
		redir = (t_token *)r->content;
		j = 0;
		while (j < indent + 1)
		{
			printf("  ");
			j++;
		}
		printf("REDIR: %s -> %s\n", token_type_str(redir->type), redir->value);
		r = r->next;
	}
}

void	print_token(void *arg)
{
	t_token	*token;

	token = (t_token *)arg;
	printf(" [%s]", token->value);
}

void	print_ast(t_ast *ast, int indent)
{
	int	i;

	if (!ast)
		return ;
	i = 0;
	while (i < indent)
	{
		printf("  ");
		i++;
	}
	if (ast->type == AST_COMMAND)
		print_command(ast, indent);
	else if (ast->type == AST_PIPE)
		printf("PIPE\n");
	else if (ast->type == AST_AND)
		printf("AND\n");
	else if (ast->type == AST_OR)
		printf("OR\n");
	else if (ast->type == AST_SUBSHELL)
		printf("GROUP\n");
	print_ast(ast->left, indent + 1);
	print_ast(ast->right, indent + 1);
}
