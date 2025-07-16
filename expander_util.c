/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:42:54 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 16:13:30 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft/libft.h"

bool	ifs_delim(char c, const char *ifs)
{
	while (*ifs)
	{
		if (*ifs == c && !ft_isspace(*ifs))
			return (true);
		ifs++;
	}
	return (false);
}

bool	ifs_whitespace(char c, const char *ifs)
{
	while (*ifs)
	{
		if (*ifs == c && (*ifs == ' ' || *ifs == '\t' || *ifs == '\n'))
			return (true);
		ifs++;
	}
	return (false);
}
