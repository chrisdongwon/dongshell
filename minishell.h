/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:30:49 by cwon              #+#    #+#             */
/*   Updated: 2025/05/22 07:44:34 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>

# include "parser.h"
# include "signal_handler.h"

typedef struct s_shell	t_shell;

struct s_shell
{
	char		*command;
	char		*prompt;
	int			last_exit_status;
	t_ast		*ast;
	t_lexer		lexer;
	t_list		*token_list;
	t_parser	parser;
};

// flush.c
void	error_exit(t_shell *shell, const char *error_message);
void	flush_lexer(t_lexer *lexer);
void	flush(t_shell *shell);

// init.c
bool	init_lexer(t_lexer *lexer);
void	init_parser(t_shell *shell);
void	init_shell(t_shell *shell);

// minishell_util.c
void	lexer(t_shell *shell);
void	parser(t_shell *shell);
void	read_command(t_shell *shell);

// minishell.c
const char *token_type_to_string(t_token_type type);
void	print_token(void *arg);
void	print_value(void *arg);
void	print_redirects(t_list *redir);
void	print_ast(t_ast *ast, int indent) ;
void	minishell(char **envp);

// prompt.c
char	*generate_prompt(void);

#endif
