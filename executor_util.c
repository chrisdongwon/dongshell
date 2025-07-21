/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:16:14 by cwon              #+#    #+#             */
/*   Updated: 2025/07/21 15:37:31 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "executor.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

static void	free_argv_arr(t_shell *shell, char **arr, size_t n)
{
	while (n)
		free(arr[--n]);
	free(arr);
	flush_and_exit(shell, "ft_strdup", EXIT_FAILURE);
}

char	**list_to_argv_array(t_shell *shell, t_list *argv_list)
{
	char	**result;
	size_t	count;
	size_t	i;
	t_token	*token;

	count = ft_lstsize(argv_list);
	result = malloc((count + 1) * sizeof(char *));
	if (!result)
		flush_and_exit(shell, "malloc", EXIT_FAILURE);
	i = 0;
	while (i < count)
	{
		token = (t_token *)argv_list->content;
		result[i] = ft_strdup(token->value);
		if (!result[i])
			free_argv_arr(shell, result, i);
		i++;
		argv_list = argv_list->next;
	}
	result[count] = 0;
	return (result);
}

void	free_str_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	remove_empty_tokens(t_list **argv_list)
{
	t_list	*curr;
	t_list	*prev;
	t_list	*to_delete;
	t_token	*token;

	curr = *argv_list;
	prev = 0;
	while (curr)
	{
		token = (t_token *)curr->content;
		if (!token->value || !token->value[0])
		{
			to_delete = curr;
			if (prev)
				prev->next = curr->next;
			else
				*argv_list = curr->next;
			curr = curr->next;
			free_token(token);
			free(to_delete);
			continue ;
		}
		prev = curr;
		curr = curr->next;
	}
}
