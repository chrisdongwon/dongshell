/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 07:48:19 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 16:56:21 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	ptr = malloc(len + 1);
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
