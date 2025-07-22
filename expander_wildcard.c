/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:38:21 by cwon              #+#    #+#             */
/*   Updated: 2025/07/22 13:51:29 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "expander.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

static bool	match_wildcard(const char *pattern, const char *string)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (true);
			while (*string)
			{
				if (match_wildcard(pattern, string))
					return (true);
				string++;
			}
			return (false);
		}
		else if (*pattern != *string)
			return (false);
		pattern++;
		string++;
	}
	return (!*string);
}

static void	ambiguous_redirect(t_shell *shell, t_list **expanded, \
t_token *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(token->value, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	ft_lstclear(expanded, free_token);
	shell->expander->sub_error = true;
}

static void	try_append_match(t_shell *shell, t_list **matches, \
const char *filename, t_token_type token_type)
{
	if (!append_new_token(matches, filename, token_type, 0))
	{
		ft_lstclear(matches, free_token);
		flush_and_exit(shell, "append_new_token", EXIT_FAILURE);
	}
}

t_list	*expand_pattern(t_shell *shell, const char *pattern, \
t_token_type token_type)
{
	const char	*filename;
	DIR			*dir;
	t_dirent	*entry;
	t_list		*matches;

	matches = 0;
	dir = opendir(".");
	if (!dir)
		flush_and_exit(shell, "opendir", EXIT_FAILURE);
	entry = readdir(dir);
	while (entry)
	{
		filename = entry->d_name;
		if (!(filename[0] == '.' && pattern[0] != '.'))
		{
			if (match_wildcard(pattern, filename))
				try_append_match(shell, &matches, filename, token_type);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (matches)
		matches = mergesort_token(matches);
	return (matches);
}

void	expand_wildcard_list(t_shell *shell, t_list **list, bool is_argv)
{
	t_list	*expanded;
	t_list	*node;
	t_token	*token;

	node = *list;
	while (node)
	{
		token = (t_token *)node->content;
		if (!token->quote && token->value && ft_strchr(token->value, '*') && \
token->type != TOKEN_HEREDOC)
		{
			expanded = expand_pattern(shell, token->value, token->type);
			if (!expanded || !ft_lstsize(expanded))
				node = node->next;
			else
			{
				if (!is_argv && ft_lstsize(expanded) > 1)
					return (ambiguous_redirect(shell, &expanded, token));
				node = replace_node(list, node, expanded);
			}
		}
		else
			node = node->next;
	}
}
