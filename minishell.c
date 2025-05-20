/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:17:46 by cwon              #+#    #+#             */
/*   Updated: 2025/05/20 18:52:07 by cwon             ###   ########.fr       */
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
			ft_lstiter(shell.token_list, print_token);
		flush(&shell);
	}
}
