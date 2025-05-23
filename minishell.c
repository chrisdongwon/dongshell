/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:17:46 by cwon              #+#    #+#             */
/*   Updated: 2025/05/23 10:07:47 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *token_type_to_string(t_token_type type)
{
	switch (type)
	{
		case TOKEN_AND:         return "TOKEN_AND";
		case TOKEN_APPEND:      return "TOKEN_APPEND";
		case TOKEN_END:         return "TOKEN_END";
		case TOKEN_ERROR:       return "TOKEN_ERROR";
		case TOKEN_HEREDOC:     return "TOKEN_HEREDOC";
		case TOKEN_OR:          return "TOKEN_OR";
		case TOKEN_PAREN_CLOSE: return "TOKEN_PAREN_CLOSE";
		case TOKEN_PAREN_OPEN:  return "TOKEN_PAREN_OPEN";
		case TOKEN_PIPE:        return "TOKEN_PIPE";
		case TOKEN_REDIR_IN:    return "TOKEN_REDIR_IN";
		case TOKEN_REDIR_OUT:   return "TOKEN_REDIR_OUT";
		case TOKEN_WORD:        return "TOKEN_WORD";
		default:                return "UNKNOWN_TOKEN";
	}
}

void	print_token(void *arg)
{
	t_token			*token;

	token = (t_token *)arg;
	if (!token)	
		return ;
	printf("[Type: %s] [Value: %s] [Quote: %c]\n",
token_type_to_string(token->type), token->value, token->quote);
}

void	print_value(void *arg)
{
	t_token			*token;

	token = (t_token *)arg;
	if (!token)
		return ;
	printf(" %s", token->value);
}

void print_redirects(t_list *redir)
{
	t_token	*token;

    while (redir)
	{
		token = (t_token *)redir->content;
        const char *type = "";
        switch (token->type)
		{
            case TOKEN_REDIR_IN:     type = "<"; break;
            case TOKEN_REDIR_OUT:    type = ">"; break;
            case TOKEN_APPEND: type = ">>"; break;
            case TOKEN_HEREDOC: type = "<<"; break;
			default: type = "";
        }
        printf(" %s %s", type, token->value);
        redir = redir->next;
    }
}

void print_ast(t_ast *ast, int indent) 
{
    if (!ast) return;
    for (int i = 0; i < indent; ++i) printf("  ");

    switch (ast->type) {
        case AST_COMMAND:
            printf("COMMAND:");
            ft_lstiter(ast->argv_list, print_value);
            print_redirects(ast->redir_list);
            printf("\n");
            break;

        case AST_PIPE:
            printf("PIPE:\n");
            print_ast(ast->left, indent + 1);
            print_ast(ast->right, indent + 1);
            break;

        case AST_AND:
            printf("AND:\n");
            print_ast(ast->left, indent + 1);
            print_ast(ast->right, indent + 1);
            break;

        case AST_OR:
            printf("OR:\n");
            print_ast(ast->left, indent + 1);
            print_ast(ast->right, indent + 1);
            break;

        case AST_SUBSHELL:
            printf("SUBSHELL:\n");
            print_ast(ast->left, indent + 1);
			if (ast->redir_list)
			{
				for (int i = 0; i < indent + 1; ++i) printf("  ");
				printf("Redirections:");
				print_redirects(ast->redir_list);
				printf("\n");
			}
            break;
    }
}

void	minishell(char **envp)
{
	t_shell	shell;

	(void)envp;
	init_shell(&shell);
	setup_signal_handlers();
	while (true)
	{
		read_command(&shell);
		lexer(&shell);
		if (!shell.lexer.success)
			printf("minishell: syntax error\n");
		else
			parser(&shell);
		flush(&shell);
	}
}
