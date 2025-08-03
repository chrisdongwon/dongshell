/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:53:48 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 10:41:09 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_string.h
 * @brief Dynamic string manipulation utilities.
 *
 * This module provides a simple dynamic string structure (`t_string`) and
 * functions for creating, appending to, and freeing dynamic strings.
 * Strings are automatically resized when needed.
 */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stdbool.h>

typedef struct s_string	t_string;

/**
 * @struct s_string
 * @brief Represents a dynamically resizable string.
 *
 * This structure holds a character buffer, its allocated capacity, 
 * and the current length of the string (excluding the null terminator).
 */
struct s_string
{
	char	*buffer;
	size_t	capacity;
	size_t	size;
};

/**
 * @brief Append a single character to a dynamic string.
 *
 * If the string buffer is not large enough, it will be reallocated
 * to accommodate the new character.
 *
 * @param str Pointer to the dynamic string.
 * @param c   Character to append.
 * @return true if the operation succeeded, false on allocation failure.
 */
bool	append_char(t_string *str, char c);

/**
 * @brief Append a C-string to a dynamic string.
 *
 * The input string `ptr` must be null-terminated.
 * The dynamic string will be resized if necessary.
 * Allocated memory is deallocated upon failue.
 *
 * @param str Pointer to the dynamic string.
 * @param ptr Null-terminated C-string to append.
 * @return true if the operation succeeded, false on allocation failure.
 */
bool	append_string(t_string *str, const char *ptr);

/**
 * @brief Initialize a dynamic string.
 *
 * This function sets the buffer to an initial size and initializes
 * the capacity and size fields. The string will be empty after initialization.
 * Allocated memory is deallocated upon failue.
 *
 * @param str Pointer to the dynamic string to initialize.
 * @return true if initialization succeeded, false on allocation failure.
 */
bool	init_string(t_string *str);

/**
 * @brief Free the memory used by a dynamic string.
 *
 * This function releases the allocated buffer and resets the capacity
 * and size fields to zero.
 *
 * @param str Pointer to the dynamic string to free.
 */
void	free_string(t_string *str);

#endif /* FT_STRING_H */
