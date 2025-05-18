/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:04:28 by cwon              #+#    #+#             */
/*   Updated: 2025/05/06 16:52:46 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	hex_length(unsigned long n)
{
	size_t	len;

	len = 0;
	if (!n)
		return (1);
	while (n)
	{
		len++;
		n /= 16;
	}
	return (len);
}

static char	*to_hex_string(unsigned long n, const char *hex)
{
	size_t	len;
	char	*result;

	len = hex_length(n) + 2;
	result = (char *)malloc(len + 1);
	if (!result)
		return (0);
	result[len--] = 0;
	if (!n)
		result[len--] = '0';
	else
	{
		while (n)
		{
			result[len--] = hex[n % 16];
			n /= 16;
		}
	}
	result[len--] = 'x';
	result[len] = '0';
	return (result);
}

void	convert_pointer(va_list *args, int *count, t_spec spec)
{
	void	*ptr;
	char	*str;

	ptr = va_arg(*args, void *);
	if (!ptr)
		str = ft_strdup("(nil)");
	else
		str = to_hex_string((unsigned long)ptr, "0123456789abcdef");
	if (str)
		return (format_print(spec, str, count));
	return (flush_printf(count, str));
}
