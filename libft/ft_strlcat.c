/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:47:08 by cwon              #+#    #+#             */
/*   Updated: 2024/09/07 17:52:09 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	concatenate(char **ptr_d, const char **ptr_s, size_t n)
{
	while (**ptr_s)
	{
		if (n != 1)
		{
			**ptr_d = **ptr_s;
			(*ptr_d)++;
			n--;
		}
		(*ptr_s)++;
	}
	**ptr_d = 0;
}

// attaches src at the end of dst.
// size - 1 chars are copied. -1 for the last null character.
// null terminated unless size is less than or equal to the dst_len
// if size is smaller than dst_len, then nothing gets "copied"
// return value is always the theoretical length of concatenation.
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*ptr_d;
	const char	*ptr_s;
	size_t		n;
	size_t		dst_len;

	ptr_d = dst;
	ptr_s = src;
	n = size;
	while (n-- && *ptr_d)
		ptr_d++;
	dst_len = ptr_d - dst;
	n = size - dst_len;
	if (!n)
		return (dst_len + ft_strlen(src));
	concatenate(&ptr_d, &ptr_s, n);
	return (dst_len + (ptr_s - src));
}
