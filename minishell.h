/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:30:49 by cwon              #+#    #+#             */
/*   Updated: 2025/07/08 14:33:49 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>

# include "executor.h"
# include "signal_handler.h"

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
void	minishell(char **envp);

// prompt.c
void	read_command(t_shell *shell);

// minishell_print.c (delete after)
void	print_token(void *arg);
void	print_ast(t_ast *ast, int indent);

#endif
