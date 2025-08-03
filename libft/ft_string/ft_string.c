/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:56:17 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 10:35:04 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../libft.h"
#include "ft_string.h"

/**
 * @brief Double the capacity of a dynamic string until it meets a minimum 
 *        requirement.
 *
 * This function increases the capacity of the given dynamic string `str`
 * by repeatedly doubling it until it is at least `min_capacity`. The buffer
 * is reallocated using `ft_str_realloc`, preserving its current contents.
 * 
 * If the reallocation fails, the string is freed via `free_string()` and
 * the function returns `false`.
 *
 * @param str          Pointer to the dynamic string whose capacity should be
 *                     increased.
 * @param min_capacity The minimum capacity required after resizing.
 *
 * @return `true` if the buffer was successfully reallocated, `false` if memory
 *         allocation failed (in which case the string is freed).
 *
 * @note The `min_capacity` is compared against the current `capacity` field, 
 *       not the string's current size.
 * @warning On failure, the dynamic string becomes empty and its buffer is 
 *          freed.
 */
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
	str->buffer = malloc(1);
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
