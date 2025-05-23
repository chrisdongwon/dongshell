/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:56:17 by cwon              #+#    #+#             */
/*   Updated: 2025/05/22 15:08:52 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static bool	double_capacity(t_string *str, size_t min_capacity)
{
	size_t	new_capacity;

	new_capacity = str->capacity;
	while (new_capacity < min_capacity)
		new_capacity *= 2;
	str->buffer = ft_str_realloc(str->buffer, str->capacity, new_capacity);
	if (!str->buffer)
	{
		free_string(str);
		return (false);
	}
	str->capacity = new_capacity;
	return (true);
}

bool	append_char(t_string *str, char c)
{
	if ((str->size + 1 >= str->capacity) && \
!double_capacity(str, str->size + 2))
		return (false);
	str->buffer[str->size++] = c;
	str->buffer[str->size] = 0;
	return (true);
}

bool	append_string(t_string *str, const char *ptr)
{
	size_t	len;

	len = ft_strlen(ptr);
	if ((str->size + len + 1 >= str->capacity) && \
!double_capacity(str, str->size + len + 1))
		return (false);
	ft_memcpy(str->buffer + str->size, ptr, len);
	str->size += len;
	str->buffer[str->size] = 0;
	return (true);
}

bool	init_string(t_string *str)
{
	str->buffer = (char *)malloc(1);
	if (!str->buffer)
		return (false);
	str->buffer[0] = 0;
	str->capacity = 1;
	str->size = 0;
	return (true);
}

void	free_string(t_string *str)
{
	free(str->buffer);
	str->buffer = 0;
	str->capacity = 0;
	str->size = 0;
}
