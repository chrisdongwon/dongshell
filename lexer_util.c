/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:09:35 by cwon              #+#    #+#             */
/*   Updated: 2025/05/13 20:00:55 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	close_quotes(const char **s)
{
	(*s)++;
	return (false);
}

bool	open_quotes(const char **s, char *quote)
{
	*quote = **s;
	(*s)++;
	return (true);
}

static void	init_ops(char **ops)
{
	ops[0] = "<<";
	ops[1] = ">>";
	ops[2] = "||";
	ops[3] = "&&";
	ops[4] = "<";
	ops[5] = ">";
	ops[6] = "|";
	ops[7] = "(";
	ops[8] = ")";
	ops[9] = 0;
}

size_t	match_operator(const char *s, char *buffer)
{
	char	*ops[10];
	size_t	i;
	size_t	len;

	init_ops(ops);
	i = 0;
	while (ops[i])
	{
		len = ft_strlen(ops[i]);
		if (!ft_strncmp(s, ops[i], len))
		{
			ft_strlcpy(buffer, ops[i], sizeof(buffer));
			buffer[len] = 0;
			return (len);
		}
		i++;
	}
	return (0);
}

t_token_type	get_token_type(const char *op)
{
	if (!ft_strncmp(op, "&&", 3))
		return (TOKEN_AND);
	if (!ft_strncmp(op, ">>", 3))
		return (TOKEN_APPEND);
	if (!ft_strncmp(op, "<<", 3))
		return (TOKEN_HEREDOC);
	if (!ft_strncmp(op, "||", 3))
		return (TOKEN_OR);
	if (!ft_strncmp(op, ")", 1))
		return (TOKEN_PAREN_CLOSE);
	if (!ft_strncmp(op, "(", 1))
		return (TOKEN_PAREN_OPEN);
	if (!ft_strncmp(op, "|", 2))
		return (TOKEN_PIPE);
	if (!ft_strncmp(op, "<", 2))
		return (TOKEN_REDIR_IN);
	if (!ft_strncmp(op, ">", 2))
		return (TOKEN_REDIR_OUT);
	return (TOKEN_ERROR);
}
