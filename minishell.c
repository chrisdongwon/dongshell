/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:17:46 by cwon              #+#    #+#             */
/*   Updated: 2025/05/25 23:50:53 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer(t_shell *shell)
{
	const char	*ptr;
	t_token		*token;

	flush_lexer(&shell->lexer);
	if (!init_lexer(&shell->lexer))
		return (perror("init_lexer (from lexer) failed"));
	ptr = shell->command;
	token = get_next_token(&shell->lexer, &ptr);
	if (!token)
		return (perror("get_next_token (from lexer) failed"));
	while (token->type != TOKEN_END && token->type != TOKEN_ERROR)
	{
		if (!add_token(&shell->token_list, token))
			return (free_token(token));
		free_string(&shell->lexer.str);
		if (!init_string(&shell->lexer.str))
			return (perror("init_string (from lexer) failed"));
		token = get_next_token(&shell->lexer, &ptr);
		if (!token)
			return (perror("get_next_token (from lexer) failed"));
	}
	if (token->type == TOKEN_ERROR)
		shell->lexer.success = false;
	free_token(token);
}

static void	parser(t_shell *shell)
{
	init_parser(shell);
	shell->ast = parse(&shell->parser);
	if (shell->parser.system_error)
		return ;
	if (shell->parser.syntax_error)
		printf("minishell: syntax error\n");
	else
		printf("parser success\n");
}

static void	read_command(t_shell *shell)
{
	shell->prompt = get_prompt(shell->envp_list);
	if (!shell->prompt)
	{
		perror("get_prompt (from build_prompt) failed");
		flush_shell(shell);
		exit(EXIT_FAILURE);
	}
	shell->command = readline(shell->prompt);
	if (!shell->command)
	{
		printf("exit\n");
		flush_shell(shell);
		ft_lstclear(&shell->envp_list, free_envp);
		exit(EXIT_SUCCESS);
	}
	if (*(shell->command))
		add_history(shell->command);
}

void	minishell(char **envp)
{
	t_shell	shell;

	init_shell(&shell, envp);
	while (true)
	{
		read_command(&shell);
		lexer(&shell);
		if (!shell.lexer.success)
			printf("minishell: syntax error\n");
		else
			parser(&shell);
		flush_shell(&shell);
	}
}
