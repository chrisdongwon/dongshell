/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:30:49 by cwon              #+#    #+#             */
/*   Updated: 2025/06/03 14:32:37 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>

# include "envp.h"
# include "lexer.h"
# include "parser.h"
# include "signal_handler.h"

typedef struct s_shell	t_shell;

struct s_shell
{
	char		*command;
	char		*prompt;
	int			last_exit_status;
	t_lexer		*lexer;
	t_list		*envp_list;
	t_parser	*parser;
};

// lexer.c
bool	lexer(t_shell *shell);
void	flush_lexer(t_shell *shell);
void	init_lexer(t_shell *shell);

// minishell_util.c
void	init_envp(t_shell *shell, char **envp);

// minishell.c
void	error_exit(t_shell *shell, const char *message);
void	flush_shell(t_shell *shell);
void	minishell(char **envp);

// parser_pipeline.c
t_ast	*parse_pipeline(t_shell *shell);

// parser.c
bool	parser(t_shell *shell);
t_ast	*parse(t_shell *shell);
void	flush_parser(t_shell *shell);
void	init_parser(t_shell *shell);

// prompt.c
void	read_command(t_shell *shell);

#endif
