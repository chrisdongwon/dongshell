/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:17:46 by cwon              #+#    #+#             */
/*   Updated: 2025/06/03 15:00:30 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_shell *shell, char **envp)
{
	shell->command = 0;
	shell->prompt = 0;
	shell->last_exit_status = 0;
	shell->envp_list = 0;
	shell->lexer = 0;
	shell->parser = 0;
	init_envp(shell, envp);
	setup_signal_handlers();
}

// exit(EXIT_FAILURE) eventually needs to be updated to indicate
// the exit signal of the failed child process...?
void	error_exit(t_shell *shell, const char *message)
{
	perror(message);
	flush_shell(shell);
	ft_lstclear(&shell->envp_list, free_envp);
	exit(EXIT_FAILURE);
}

void	flush_shell(t_shell *shell)
{
	free(shell->command);
	free(shell->prompt);
	flush_lexer(shell);
	flush_parser(shell);
}

// delete after testing
void	print_token(void *arg)
{
	t_token *token;

	token = (t_token *)arg;
	printf(" %s", token->value);
}

// delete after testing
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
		default:                return "UNKNOWN_TOKEN_TYPE";
	}
}

// delete after testing
void	print_ast(t_ast *ast, int indent)
{
	if (!ast)
		return ;
	for (int i = 0; i < indent; i++)
		printf("  ");
	switch (ast->type)
	{
		case AST_COMMAND:
			printf("COMMAND:");
			ft_lstiter(ast->argv_list, print_token);
			printf("\n");
			for (t_list *r = ast->redir_list; r; r = r->next)
			{
				t_token *redir = r->content;
				for (int i = 0; i < indent + 1; i++) printf("  ");
				printf("REDIR: %s -> %s\n", token_type_to_string(redir->type), redir->value);
			}
			break;
		case AST_PIPE:     printf("PIPE\n"); break;
		case AST_AND:      printf("AND\n"); break;
		case AST_OR:       printf("OR\n"); break;
		case AST_SUBSHELL: printf("GROUP\n"); break;
	}
	print_ast(ast->left, indent + 1);
	print_ast(ast->right, indent + 1);
}

void	minishell(char **envp)
{
	t_shell	shell;

	init_shell(&shell, envp);
	while (true)
	{
		read_command(&shell);
		if (lexer(&shell) && parser(&shell))
		{
			if (expander(&shell))
				printf("continue with command execution\n");
			else
				printf("minishell: bad substitution\n");
		}
		else
			printf("minishell: syntax error\n");
		flush_shell(&shell);
	}
}
