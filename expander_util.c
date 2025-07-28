/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:42:54 by cwon              #+#    #+#             */
/*   Updated: 2025/07/27 17:53:12 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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

char	*make_temp_filename(int i)
{
	char		*nptr;
	char		*result;
	t_string	str;

	if (!init_string(&str) || !append_string(&str, "/tmp/minishell_heredoc_"))
		return (0);
	nptr = ft_itoa(i);
	if (!nptr)
		return (0);
	if (!append_string(&str, nptr))
		return (0);
	free(nptr);
	result = ft_strdup(str.buffer);
	free_string(&str);
	return (result);
}
