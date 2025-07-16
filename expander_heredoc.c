/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:36:27 by cwon              #+#    #+#             */
/*   Updated: 2025/07/12 21:32:06 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "expander.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

static char	*make_temp_filename(int i)
{
	char		*nptr;
	char		*result;
	t_string	str;

	if (!init_string(&str))
		return (0);
	if (!append_string(&str, "/tmp/minishell_heredoc_"))
	{
		free_string(&str);
		return (0);
	}
	nptr = ft_itoa(i);
	if (!nptr)
	{
		free_string(&str);
		return (0);
	}
	if (!append_string(&str, nptr))
	{
		free_string(&str);
		return (0);
	}
	result = ft_strdup(str.buffer);
	free_string(&str);
	return (result);
}

static t_token	*find_next_heredoc_token(t_list **redir_node)
{
	t_token	*token;

	while (*redir_node)
	{
		token = (*redir_node)->content;
		if (token->type == TOKEN_HEREDOC)
			return (token);
		*redir_node = (*redir_node)->next;
	}
	return (0);
}

static bool	process_heredoc(int i, const char *delim, t_token *token)
{
	char	*temp_filename;

	temp_filename = make_temp_filename(i);
	if (!temp_filename || !collect_heredoc(delim, temp_filename))
		return (false);
	free(token->value);
	token->value = temp_filename;
	return (true);
}

void	prepare_heredocs(t_shell *shell, t_ast *ast)
{
	char	*delim;
	int		i;
	t_list	*delim_node;
	t_list	*redir_node;
	t_token	*token;

	delim_node = ast->heredoc_delim;
	redir_node = ast->redir_list;
	i = 0;
	while (delim_node)
	{
		delim = delim_node->content;
		token = find_next_heredoc_token(&redir_node);
		if (!token)
			flush_and_exit(shell, "find_next_heredoc_token", EXIT_FAILURE);
		if (!process_heredoc(i++, delim, token))
			flush_and_exit(shell, "process_heredoc", EXIT_FAILURE);
		delim_node = delim_node->next;
		if (redir_node)
			redir_node = redir_node->next;
	}
}
