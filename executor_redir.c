/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:37:19 by cwon              #+#    #+#             */
/*   Updated: 2025/07/11 18:46:38 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

static void	redirect_input(t_shell *shell, const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		flush_and_exit(shell, "open", EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		flush_and_exit(shell, "dup2", EXIT_FAILURE);
	}
	close(fd);
}

static void	redirect_output(t_shell *shell, const char *filename, int flags)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | flags, 0644);
	if (fd < 0)
		flush_and_exit(shell, "open", EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		flush_and_exit(shell, "dup2", EXIT_FAILURE);
	}
	close(fd);
}

void	apply_redirections(t_shell *shell, t_list *redir_list)
{
	t_token	*token;

	while (redir_list)
	{
		token = (t_token *)redir_list->content;
		if (token->type == TOKEN_REDIR_IN)
			redirect_input(shell, token->value);
		else if (token->type == TOKEN_REDIR_OUT)
			redirect_output(shell, token->value, O_TRUNC);
		else if (token->type == TOKEN_APPEND)
			redirect_output(shell, token->value, O_APPEND);
		else if (token->type == TOKEN_HEREDOC)
			redirect_input(shell, token->value);
		redir_list = redir_list->next;
	}
}
