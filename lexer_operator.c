/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:53:07 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 10:48:16 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"

/**
 * @brief Initialize the list of shell operator strings.
 *
 * Populates the provided array with known shell operators,
 * including redirections, logical operators, pipes, and
 * parentheses. The array is terminated with a NULL pointer.
 *
 * @param ops Array of 10 char pointers to store operator strings.
 */
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

/**
 * @brief Match an operator at the start of a string.
 *
 * Compares the start of the input string against known shell
 * operators. If a match is found, copies the matched operator
 * into the provided buffer and returns its length.
 *
 * @param s      Pointer to the input string to check.
 * @param buffer Buffer to store the matched operator string.
 *               Must be large enough to hold the operator and
 *               a null terminator.
 *
 * @return Length of the matched operator, or 0 if no match is found.
 */
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
