/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:26:27 by cwon              #+#    #+#             */
/*   Updated: 2024/09/08 17:07:35 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	i;
	size_t	len;

	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	result = (char *)malloc(len + 1);
	if (result)
	{
		i = 0;
		while (i < len)
		{
			result[i] = (*f)(i, s[i]);
			i++;
		}
		result[i] = 0;
	}
	return (result);
}
