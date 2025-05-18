/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnmatch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 00:01:10 by cwon              #+#    #+#             */
/*   Updated: 2025/05/11 01:07:57 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fnmatch(const char *pattern, const char *string)
{
	if (!*pattern)
		return (*string);
	if (ft_strncmp(pattern, "*", 2))
		return (0);
	if (*pattern == '*')
	{
		if (!ft_fnmatch(pattern + 1, string))
			return (0);
		if (!*string)
			return (1);
		return (ft_fnmatch(pattern, string + 1));
	}
	if (*pattern != *string)
		return (1);
	return (ft_fnmatch(pattern + 1, string + 1));
}
