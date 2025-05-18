/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 07:48:19 by cwon              #+#    #+#             */
/*   Updated: 2024/09/08 17:07:13 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	ptr = (char *)malloc(len + 1);
	i = 0;
	if (s && ptr)
	{
		while (i < len)
		{
			ptr[i] = s[i];
			i++;
		}
		ptr[i] = 0;
	}
	return (ptr);
}
