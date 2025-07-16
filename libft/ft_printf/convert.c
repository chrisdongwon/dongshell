/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 01:29:48 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 17:08:38 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../libft.h"
#include "ft_printf.h"

void	convert(t_spec spec, va_list *args, int *count)
{
	if (spec.type == 'c')
		convert_char(args, count, spec);
	else if (spec.type == 's')
		convert_string(args, count, spec);
	else if (spec.type == 'd' || spec.type == 'i')
		convert_int(args, count, spec);
	else if (spec.type == 'u')
		convert_unsigned(args, count, spec);
	else if (spec.type == 'x')
		convert_hex(args, count, spec, "0123456789abcdef");
	else if (spec.type == 'X')
		convert_hex(args, count, spec, "0123456789ABCDEF");
	else if (spec.type == 'p')
		convert_pointer(args, count, spec);
	else if (spec.type == '%')
		convert_percent_literal(count);
}

void	empty_str(char **str)
{
	free(*str);
	*str = ft_strdup("");
}

void	flush_printf(int *count, char *str)
{
	*count = -1;
	free(str);
}

void	format_print(t_spec spec, char *str, int *count)
{
	char	*space_pad;
	size_t	len;
	size_t	space_len;

	len = ft_strlen(str);
	space_len = 0;
	if (spec.width > len)
		space_len = spec.width - len;
	space_pad = pad_string(space_len, ' ');
	if (!space_pad)
		return (flush_printf(count, str));
	if (!spec.minus)
		put_space(space_pad, space_len, count);
	if (*count != -1 && ft_putstr_fd(str, 1) >= 0)
		*count += len;
	else
	{
		free(space_pad);
		return (flush_printf(count, str));
	}
	if (spec.minus)
		put_space(space_pad, space_len, count);
	free(space_pad);
	free(str);
}
