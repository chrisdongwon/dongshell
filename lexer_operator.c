/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:53:07 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 16:15:39 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"

static void	init_operators(char **ops)
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

static size_t	match_operator(const char *s, char *buffer)
{
	char	*ops[10];
	size_t	i;
	size_t	len;

	init_operators(ops);
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

t_token	*handle_operator(const char **input, const char *s)
{
	char		buffer[3];
	size_t		len;

	ft_bzero(buffer, 3);
	len = match_operator(s, buffer);
	if (!len)
		return (new_token("Unknown operator", 16, TOKEN_ERROR, 0));
	*input = s + len;
	return (new_token(buffer, len, get_token_type(buffer), 0));
}
