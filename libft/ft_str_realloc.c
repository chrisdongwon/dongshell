/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_realloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:22:32 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 16:56:14 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_str_realloc(char *ptr, size_t old_size, size_t new_size)
{
	char	*result;
	size_t	size;

	if (!new_size)
	{
		free(ptr);
		return (0);
	}
	result = malloc(new_size);
	if (!result)
		return (0);
	if (!ptr)
		return (result);
	size = new_size;
	if (old_size < new_size)
		size = old_size;
	ft_memcpy(result, ptr, size);
	free(ptr);
	return (result);
}
