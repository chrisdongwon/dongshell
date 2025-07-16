/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:16:14 by cwon              #+#    #+#             */
/*   Updated: 2025/07/15 12:09:10 by cwon             ###   ########.fr       */
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
