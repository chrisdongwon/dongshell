/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:30:49 by cwon              #+#    #+#             */
/*   Updated: 2025/05/25 23:50:17 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>

# include "envp.h"
# include "parser.h"
# include "signal_handler.h"

typedef struct s_shell	t_shell;

struct s_shell
{
	char		*command;
	char		*prompt;
	t_ast		*ast;
	t_lexer		lexer;
	t_list		*envp_list;
	t_list		*token_list;
	t_parser	parser;
};

// flush.c
void	flush_lexer(t_lexer *lexer);
void	flush_shell(t_shell *shell);

// init.c
bool	init_lexer(t_lexer *lexer);
void	init_parser(t_shell *shell);
void	init_shell(t_shell *shell, char **envp);

// minishell.c
void	minishell(char **envp);

// prompt.c
char	*get_prompt(t_list *envp_list);

#endif
