/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:21:21 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 17:11:33 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../libft.h"
#include "ft_printf.h"

static void	add_header(char *result, const char *hex)
{
	if (hex[10] == 'a')
		result[1] = 'x';
	else
		result[1] = 'X';
	result[0] = '0';
}

static size_t	hex_length(unsigned int n)
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

static char	*to_hex_string(unsigned int n, t_spec spec, const char *hex)
{
	char	*result;
	size_t	len;

	len = hex_length(n);
	if (spec.pound && n)
		len += 2;
	result = malloc(len + 1);
	if (!result)
		return (0);
	result[len--] = 0;
	if (!n)
		result[len] = '0';
	else if (spec.pound)
		add_header(result, hex);
	while (n)
	{
		result[len--] = hex[n % 16];
		n /= 16;
	}
	return (result);
}

void	convert_hex(va_list *args, int *count, t_spec spec, const char *hex)
{
	char			*str;
	size_t			digit_len;
	size_t			len;
	unsigned int	val;

	val = va_arg(*args, unsigned int);
	str = to_hex_string(val, spec, hex);
	len = ft_strlen(str);
	digit_len = len;
	if (spec.pound && val)
		digit_len -= 2;
	if (spec.dot && !spec.precision && str && str[0] == '0')
		empty_str(&str);
	if (spec.dot && spec.precision < 0)
		spec.dot = 0;
	if (spec.dot && spec.zero)
		spec.zero = 0;
	if (spec.dot && spec.precision > (int)digit_len && str)
		pad_zero(&str, spec.precision - digit_len);
	else if (spec.zero && !spec.dot && spec.width > len && str)
		pad_zero(&str, spec.width - len);
	if (!str)
		return (flush_printf(count, str));
	return (format_print(spec, str, count));
}
