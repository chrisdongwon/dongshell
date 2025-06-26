/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:30:49 by cwon              #+#    #+#             */
/*   Updated: 2025/06/26 12:03:00 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>

# include "envp.h"
# include "lexer.h"
# include "expander.h"
# include "signal_handler.h"

typedef struct s_shell	t_shell;

struct s_shell
{
	char		*command;
	char		*prompt;
	int			last_exit_status;
	t_expander	*expander;
	t_lexer		*lexer;
	t_list		*envp_list;
	t_parser	*parser;
};

// expander_split.c
void	expand_split(t_shell *shell, t_list **head, t_list **node);

// expander_var.c
void	expand_variable(t_shell *shell, t_token *token);

// expander.c
bool	expander(t_shell *shell);
void	flush_expander(t_shell *shell);

// lexer.c
bool	lexer(t_shell *shell);
void	flush_lexer(t_shell *shell);

// minishell_util.c
char	*get_ifs(t_list *envp_list);
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

// prompt.c
void	read_command(t_shell *shell);

// print utils
void	print_token(void *arg);

#endif
