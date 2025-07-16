/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:30:49 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 15:43:25 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_ast		t_ast; // do not need after deleting print functions
typedef struct s_expander	t_expander;
typedef struct s_lexer		t_lexer;
typedef struct s_list		t_list;
typedef struct s_parser		t_parser;
typedef struct s_shell		t_shell;

struct						s_ast; // do not need after deleting print funcitons
struct						s_expander;
struct						s_lexer;
struct						s_list;
struct						s_parser;

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

// minishell.c
void	flush_and_exit(t_shell *shell, const char *error_msg, int exit_status);
void	flush_shell(t_shell *shell);
void	minishell(char **envp);

// prompt.c
void	read_command(t_shell *shell);

// minishell_print.c (delete after)
void	print_token(void *arg);
void	print_ast(t_ast *ast, int indent);

#endif
