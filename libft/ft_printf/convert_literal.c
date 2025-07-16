/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_literal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:17:39 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 17:09:49 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../libft.h"
#include "ft_printf.h"

void	convert_char(va_list *args, int *count, t_spec spec)
{
	char	*space_pad;
	size_t	space_len;

	space_len = 0;
	if (spec.width > 1)
		space_len = spec.width - 1;
	space_pad = pad_string(space_len, ' ');
	if (!space_pad)
		return (flush_printf(count, space_pad));
	if (!spec.minus)
		put_space(space_pad, space_len, count);
	if (*count != -1 && ft_putchar_fd(va_arg(*args, int), 1) != -1)
		*count += 1;
	else
		return (flush_printf(count, space_pad));
	if (spec.minus)
		put_space(space_pad, space_len, count);
	free(space_pad);
}

void	convert_percent_literal(int *count)
{
	if (ft_putchar_fd('%', 1) != -1)
		*count += 1;
	else
		*count = -1;
}

void	convert_string(va_list *args, int *count, t_spec spec)
{
	char	*str;

	str = va_arg(*args, char *);
	if (str)
	{
		if (spec.dot)
			str = ft_substr(str, 0, spec.precision);
		else
			str = ft_strdup(str);
	}
	else
	{
		if (spec.dot && spec.precision < 6)
			str = ft_strdup("");
		else
			str = ft_strdup("(null)");
	}
	if (!str)
		return (flush_printf(count, str));
	return (format_print(spec, str, count));
}
