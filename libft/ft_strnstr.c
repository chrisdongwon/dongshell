/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:14:01 by cwon              #+#    #+#             */
/*   Updated: 2024/09/08 17:07:55 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!little[j])
		return ((char *)big);
	while (i < len && big[i])
	{
		while (i + j < len && big[i + j] && little[j] == big[i + j])
		{
			if (!little[++j])
				return ((char *)(big + i));
		}
		i++;
		j = 0;
	}
	return (0);
}
