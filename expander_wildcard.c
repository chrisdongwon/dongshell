/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:38:21 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 16:33:48 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>

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
				if (match_wildcard(pattern, string++))
					return (true);
			}
			return (false);
		}
		else if (*(pattern++) != *(string++))
			return (false);
	}
	return (!*string);
}

static DIR	*open_directory_or_exit(t_shell *shell)
{
	DIR	*dir;

	dir = opendir(".");
	if (!dir)
		flush_and_exit(shell, "opendir", EXIT_FAILURE);
	return (dir);
}

static void	try_append_match(t_shell *shell, t_list **matches, \
const char *filename)
{
	if (!append_new_token(matches, filename, TOKEN_WORD, 0))
	{
		ft_lstclear(matches, free_token);
		flush_and_exit(shell, "append_new_token", EXIT_FAILURE);
	}
}

static t_list	*expand_pattern(t_shell *shell, const char *pattern)
{
	const char	*filename;
	DIR			*dir;
	t_dirent	*entry;
	t_list		*matches;

	matches = 0;
	dir = open_directory_or_exit(shell);
	entry = readdir(dir);
	while (entry)
	{
		filename = entry->d_name;
		if ((filename[0] != '.' || pattern[0] == '.'))
		{
			if (match_wildcard(pattern, filename))
				try_append_match(shell, &matches, filename);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (matches && matches->next)
		matches = mergesort_token(matches);
	return (matches);
}

void	expand_wildcard(t_shell *shell, t_list **list)
{
	t_list	*expanded;
	t_list	*node;
	t_token	*token;

	node = *list;
	while (node)
	{
		token = (t_token *)node->content;
		if (!token->quote && token->value && ft_strchr(token->value, '*'))
		{
			expanded = expand_pattern(shell, token->value);
			if (expanded && ft_lstsize(expanded))
				node = replace_node(list, node, expanded);
		}
		node = node->next;
	}
}
